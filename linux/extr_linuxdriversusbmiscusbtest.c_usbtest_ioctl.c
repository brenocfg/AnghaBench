#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usbtest_param_64 {int duration_usec; int /*<<< orphan*/  duration_sec; int /*<<< orphan*/  vary; int /*<<< orphan*/  sglen; int /*<<< orphan*/  length; int /*<<< orphan*/  iterations; int /*<<< orphan*/  test_num; } ;
struct usbtest_param_32 {int duration_usec; int /*<<< orphan*/  duration_sec; int /*<<< orphan*/  vary; int /*<<< orphan*/  sglen; int /*<<< orphan*/  length; int /*<<< orphan*/  iterations; int /*<<< orphan*/  test_num; } ;
struct usbtest_dev {int /*<<< orphan*/  lock; TYPE_3__* info; } ;
struct usb_interface {int /*<<< orphan*/  dev; TYPE_2__* altsetting; } ;
struct timespec64 {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {scalar_t__ alt; } ;
struct TYPE_4__ {scalar_t__ bInterfaceNumber; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int ERESTARTSYS ; 
 int NSEC_PER_USEC ; 
#define  USBTEST_REQUEST_32 129 
#define  USBTEST_REQUEST_64 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  ktime_get_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  mod_pattern ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pattern ; 
 int set_altsetting (struct usbtest_dev*,scalar_t__) ; 
 struct timespec64 timespec64_sub (struct timespec64,struct timespec64) ; 
 struct usbtest_dev* usb_get_intfdata (struct usb_interface*) ; 
 int usbtest_do_ioctl (struct usb_interface*,struct usbtest_param_32*) ; 

__attribute__((used)) static int
usbtest_ioctl(struct usb_interface *intf, unsigned int code, void *buf)
{

	struct usbtest_dev	*dev = usb_get_intfdata(intf);
	struct usbtest_param_64 *param_64 = buf;
	struct usbtest_param_32 temp;
	struct usbtest_param_32 *param_32 = buf;
	struct timespec64 start;
	struct timespec64 end;
	struct timespec64 duration;
	int retval = -EOPNOTSUPP;

	/* FIXME USBDEVFS_CONNECTINFO doesn't say how fast the device is. */

	pattern = mod_pattern;

	if (mutex_lock_interruptible(&dev->lock))
		return -ERESTARTSYS;

	/* FIXME: What if a system sleep starts while a test is running? */

	/* some devices, like ez-usb default devices, need a non-default
	 * altsetting to have any active endpoints.  some tests change
	 * altsettings; force a default so most tests don't need to check.
	 */
	if (dev->info->alt >= 0) {
		if (intf->altsetting->desc.bInterfaceNumber) {
			retval = -ENODEV;
			goto free_mutex;
		}
		retval = set_altsetting(dev, dev->info->alt);
		if (retval) {
			dev_err(&intf->dev,
					"set altsetting to %d failed, %d\n",
					dev->info->alt, retval);
			goto free_mutex;
		}
	}

	switch (code) {
	case USBTEST_REQUEST_64:
		temp.test_num = param_64->test_num;
		temp.iterations = param_64->iterations;
		temp.length = param_64->length;
		temp.sglen = param_64->sglen;
		temp.vary = param_64->vary;
		param_32 = &temp;
		break;

	case USBTEST_REQUEST_32:
		break;

	default:
		retval = -EOPNOTSUPP;
		goto free_mutex;
	}

	ktime_get_ts64(&start);

	retval = usbtest_do_ioctl(intf, param_32);
	if (retval < 0)
		goto free_mutex;

	ktime_get_ts64(&end);

	duration = timespec64_sub(end, start);

	temp.duration_sec = duration.tv_sec;
	temp.duration_usec = duration.tv_nsec/NSEC_PER_USEC;

	switch (code) {
	case USBTEST_REQUEST_32:
		param_32->duration_sec = temp.duration_sec;
		param_32->duration_usec = temp.duration_usec;
		break;

	case USBTEST_REQUEST_64:
		param_64->duration_sec = temp.duration_sec;
		param_64->duration_usec = temp.duration_usec;
		break;
	}

free_mutex:
	mutex_unlock(&dev->lock);
	return retval;
}