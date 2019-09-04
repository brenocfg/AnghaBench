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
struct net_device {int dummy; } ;
struct iw_handler_def {unsigned int num_standard; int /*<<< orphan*/ ** standard; } ;
typedef  int /*<<< orphan*/ * iw_handler ;

/* Variables and functions */
 unsigned int IW_IOCTL_IDX (unsigned int) ; 

__attribute__((used)) static iw_handler get_handler(struct net_device *dev, unsigned int cmd)
{
	/* Don't "optimise" the following variable, it will crash */
	unsigned int	index;		/* *MUST* be unsigned */
	const struct iw_handler_def *handlers = NULL;

#ifdef CONFIG_CFG80211_WEXT
	if (dev->ieee80211_ptr && dev->ieee80211_ptr->wiphy)
		handlers = dev->ieee80211_ptr->wiphy->wext;
#endif
#ifdef CONFIG_WIRELESS_EXT
	if (dev->wireless_handlers)
		handlers = dev->wireless_handlers;
#endif

	if (!handlers)
		return NULL;

	/* Try as a standard command */
	index = IW_IOCTL_IDX(cmd);
	if (index < handlers->num_standard)
		return handlers->standard[index];

#ifdef CONFIG_WEXT_PRIV
	/* Try as a private command */
	index = cmd - SIOCIWFIRSTPRIV;
	if (index < handlers->num_private)
		return handlers->private[index];
#endif

	/* Not found */
	return NULL;
}