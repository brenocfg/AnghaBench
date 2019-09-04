#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usbnet {scalar_t__* data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cdc_ncm_ctx {unsigned long timer_interval; int /*<<< orphan*/  mtx; scalar_t__ tx_timer_pending; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 unsigned long CDC_NCM_TIMER_INTERVAL_MAX ; 
 unsigned long CDC_NCM_TIMER_INTERVAL_MIN ; 
 size_t EINVAL ; 
 unsigned long NSEC_PER_USEC ; 
 size_t kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct usbnet* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t cdc_ncm_store_tx_timer_usecs(struct device *d,  struct device_attribute *attr, const char *buf, size_t len)
{
	struct usbnet *dev = netdev_priv(to_net_dev(d));
	struct cdc_ncm_ctx *ctx = (struct cdc_ncm_ctx *)dev->data[0];
	ssize_t ret;
	unsigned long val;

	ret = kstrtoul(buf, 0, &val);
	if (ret)
		return ret;
	if (val && (val < CDC_NCM_TIMER_INTERVAL_MIN || val > CDC_NCM_TIMER_INTERVAL_MAX))
		return -EINVAL;

	spin_lock_bh(&ctx->mtx);
	ctx->timer_interval = val * NSEC_PER_USEC;
	if (!ctx->timer_interval)
		ctx->tx_timer_pending = 0;
	spin_unlock_bh(&ctx->mtx);
	return len;
}