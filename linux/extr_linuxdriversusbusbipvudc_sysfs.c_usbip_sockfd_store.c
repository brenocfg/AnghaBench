#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ status; int /*<<< orphan*/  lock; void* tcp_tx; void* tcp_rx; struct socket* tcp_socket; } ;
struct vudc {int connected; int /*<<< orphan*/  lock; TYPE_1__ ud; int /*<<< orphan*/  start_time; int /*<<< orphan*/  pullup; int /*<<< orphan*/  driver; } ;
struct socket {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 size_t EINVAL ; 
 size_t ENODEV ; 
 scalar_t__ SDEV_ST_AVAILABLE ; 
 scalar_t__ SDEV_ST_USED ; 
 int /*<<< orphan*/  VUDC_EVENT_DOWN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 void* kthread_get_run (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ktime_get_ts64 (int /*<<< orphan*/ *) ; 
 struct socket* sockfd_lookup (int,int*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usbip_event_add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_rx_loop ; 
 int /*<<< orphan*/  v_start_timer (struct vudc*) ; 
 int /*<<< orphan*/  v_tx_loop ; 

__attribute__((used)) static ssize_t usbip_sockfd_store(struct device *dev, struct device_attribute *attr,
		     const char *in, size_t count)
{
	struct vudc *udc = (struct vudc *) dev_get_drvdata(dev);
	int rv;
	int sockfd = 0;
	int err;
	struct socket *socket;
	unsigned long flags;
	int ret;

	rv = kstrtoint(in, 0, &sockfd);
	if (rv != 0)
		return -EINVAL;

	if (!udc) {
		dev_err(dev, "no device");
		return -ENODEV;
	}
	spin_lock_irqsave(&udc->lock, flags);
	/* Don't export what we don't have */
	if (!udc->driver || !udc->pullup) {
		dev_err(dev, "gadget not bound");
		ret = -ENODEV;
		goto unlock;
	}

	if (sockfd != -1) {
		if (udc->connected) {
			dev_err(dev, "Device already connected");
			ret = -EBUSY;
			goto unlock;
		}

		spin_lock_irq(&udc->ud.lock);

		if (udc->ud.status != SDEV_ST_AVAILABLE) {
			ret = -EINVAL;
			goto unlock_ud;
		}

		socket = sockfd_lookup(sockfd, &err);
		if (!socket) {
			dev_err(dev, "failed to lookup sock");
			ret = -EINVAL;
			goto unlock_ud;
		}

		udc->ud.tcp_socket = socket;

		spin_unlock_irq(&udc->ud.lock);
		spin_unlock_irqrestore(&udc->lock, flags);

		udc->ud.tcp_rx = kthread_get_run(&v_rx_loop,
						    &udc->ud, "vudc_rx");
		udc->ud.tcp_tx = kthread_get_run(&v_tx_loop,
						    &udc->ud, "vudc_tx");

		spin_lock_irqsave(&udc->lock, flags);
		spin_lock_irq(&udc->ud.lock);
		udc->ud.status = SDEV_ST_USED;
		spin_unlock_irq(&udc->ud.lock);

		ktime_get_ts64(&udc->start_time);
		v_start_timer(udc);
		udc->connected = 1;
	} else {
		if (!udc->connected) {
			dev_err(dev, "Device not connected");
			ret = -EINVAL;
			goto unlock;
		}

		spin_lock_irq(&udc->ud.lock);
		if (udc->ud.status != SDEV_ST_USED) {
			ret = -EINVAL;
			goto unlock_ud;
		}
		spin_unlock_irq(&udc->ud.lock);

		usbip_event_add(&udc->ud, VUDC_EVENT_DOWN);
	}

	spin_unlock_irqrestore(&udc->lock, flags);

	return count;

unlock_ud:
	spin_unlock_irq(&udc->ud.lock);
unlock:
	spin_unlock_irqrestore(&udc->lock, flags);

	return ret;
}