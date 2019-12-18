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
struct xt_physdev_info {int bitmask; int invert; int /*<<< orphan*/  out_mask; int /*<<< orphan*/  physoutdev; int /*<<< orphan*/  in_mask; int /*<<< orphan*/  physindev; } ;
struct xt_action_param {struct xt_physdev_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct net_device {char* name; } ;

/* Variables and functions */
 int XT_PHYSDEV_OP_BRIDGED ; 
 int XT_PHYSDEV_OP_IN ; 
 int XT_PHYSDEV_OP_ISIN ; 
 int XT_PHYSDEV_OP_ISOUT ; 
 int XT_PHYSDEV_OP_OUT ; 
 unsigned long ifname_compare_aligned (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* nf_bridge_get_physindev (struct sk_buff const*) ; 
 struct net_device* nf_bridge_get_physoutdev (struct sk_buff const*) ; 
 int /*<<< orphan*/  nf_bridge_info_exists (struct sk_buff const*) ; 

__attribute__((used)) static bool
physdev_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_physdev_info *info = par->matchinfo;
	const struct net_device *physdev;
	unsigned long ret;
	const char *indev, *outdev;

	/* Not a bridged IP packet or no info available yet:
	 * LOCAL_OUT/mangle and LOCAL_OUT/nat don't know if
	 * the destination device will be a bridge. */
	if (!nf_bridge_info_exists(skb)) {
		/* Return MATCH if the invert flags of the used options are on */
		if ((info->bitmask & XT_PHYSDEV_OP_BRIDGED) &&
		    !(info->invert & XT_PHYSDEV_OP_BRIDGED))
			return false;
		if ((info->bitmask & XT_PHYSDEV_OP_ISIN) &&
		    !(info->invert & XT_PHYSDEV_OP_ISIN))
			return false;
		if ((info->bitmask & XT_PHYSDEV_OP_ISOUT) &&
		    !(info->invert & XT_PHYSDEV_OP_ISOUT))
			return false;
		if ((info->bitmask & XT_PHYSDEV_OP_IN) &&
		    !(info->invert & XT_PHYSDEV_OP_IN))
			return false;
		if ((info->bitmask & XT_PHYSDEV_OP_OUT) &&
		    !(info->invert & XT_PHYSDEV_OP_OUT))
			return false;
		return true;
	}

	physdev = nf_bridge_get_physoutdev(skb);
	outdev = physdev ? physdev->name : NULL;

	/* This only makes sense in the FORWARD and POSTROUTING chains */
	if ((info->bitmask & XT_PHYSDEV_OP_BRIDGED) &&
	    (!!outdev ^ !(info->invert & XT_PHYSDEV_OP_BRIDGED)))
		return false;

	physdev = nf_bridge_get_physindev(skb);
	indev = physdev ? physdev->name : NULL;

	if ((info->bitmask & XT_PHYSDEV_OP_ISIN &&
	    (!indev ^ !!(info->invert & XT_PHYSDEV_OP_ISIN))) ||
	    (info->bitmask & XT_PHYSDEV_OP_ISOUT &&
	    (!outdev ^ !!(info->invert & XT_PHYSDEV_OP_ISOUT))))
		return false;

	if (!(info->bitmask & XT_PHYSDEV_OP_IN))
		goto match_outdev;

	if (indev) {
		ret = ifname_compare_aligned(indev, info->physindev,
					     info->in_mask);

		if (!ret ^ !(info->invert & XT_PHYSDEV_OP_IN))
			return false;
	}

match_outdev:
	if (!(info->bitmask & XT_PHYSDEV_OP_OUT))
		return true;

	if (!outdev)
		return false;

	ret = ifname_compare_aligned(outdev, info->physoutdev, info->out_mask);

	return (!!ret ^ !(info->invert & XT_PHYSDEV_OP_OUT));
}