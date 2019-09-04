#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_data; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct atmel_private {int BSS_list_entries; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  management_timer; TYPE_1__* BSSinfo; scalar_t__ wep_is_on; } ;
struct TYPE_2__ {int const* BSSID; scalar_t__ UsingWEP; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int EINVAL ; 
 int /*<<< orphan*/  atmel_join_bss (struct atmel_private*,int) ; 
 int /*<<< orphan*/  atmel_scan (struct atmel_private*,int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int const*,int /*<<< orphan*/ ,int) ; 
 struct atmel_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int atmel_set_wap(struct net_device *dev,
			 struct iw_request_info *info,
			 struct sockaddr *awrq,
			 char *extra)
{
	struct atmel_private *priv = netdev_priv(dev);
	int i;
	static const u8 any[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	static const u8 off[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	unsigned long flags;

	if (awrq->sa_family != ARPHRD_ETHER)
		return -EINVAL;

	if (!memcmp(any, awrq->sa_data, 6) ||
	    !memcmp(off, awrq->sa_data, 6)) {
		del_timer_sync(&priv->management_timer);
		spin_lock_irqsave(&priv->irqlock, flags);
		atmel_scan(priv, 1);
		spin_unlock_irqrestore(&priv->irqlock, flags);
		return 0;
	}

	for (i = 0; i < priv->BSS_list_entries; i++) {
		if (memcmp(priv->BSSinfo[i].BSSID, awrq->sa_data, 6) == 0) {
			if (!priv->wep_is_on && priv->BSSinfo[i].UsingWEP) {
				return -EINVAL;
			} else if  (priv->wep_is_on && !priv->BSSinfo[i].UsingWEP) {
				return -EINVAL;
			} else {
				del_timer_sync(&priv->management_timer);
				spin_lock_irqsave(&priv->irqlock, flags);
				atmel_join_bss(priv, i);
				spin_unlock_irqrestore(&priv->irqlock, flags);
				return 0;
			}
		}
	}

	return -EINVAL;
}