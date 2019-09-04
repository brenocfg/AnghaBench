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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct audit_features {int mask; int features; int lock; } ;
struct TYPE_2__ {int features; int lock; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int AUDIT_FEATURE_TO_MASK (int) ; 
 int AUDIT_LAST_FEATURE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EPERM ; 
 TYPE_1__ af ; 
 int /*<<< orphan*/  audit_feature_names ; 
 int /*<<< orphan*/  audit_log_feature_change (int,int,int,int,int,int) ; 
 struct audit_features* nlmsg_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_hdr (struct sk_buff*) ; 

__attribute__((used)) static int audit_set_feature(struct sk_buff *skb)
{
	struct audit_features *uaf;
	int i;

	BUILD_BUG_ON(AUDIT_LAST_FEATURE + 1 > ARRAY_SIZE(audit_feature_names));
	uaf = nlmsg_data(nlmsg_hdr(skb));

	/* if there is ever a version 2 we should handle that here */

	for (i = 0; i <= AUDIT_LAST_FEATURE; i++) {
		u32 feature = AUDIT_FEATURE_TO_MASK(i);
		u32 old_feature, new_feature, old_lock, new_lock;

		/* if we are not changing this feature, move along */
		if (!(feature & uaf->mask))
			continue;

		old_feature = af.features & feature;
		new_feature = uaf->features & feature;
		new_lock = (uaf->lock | af.lock) & feature;
		old_lock = af.lock & feature;

		/* are we changing a locked feature? */
		if (old_lock && (new_feature != old_feature)) {
			audit_log_feature_change(i, old_feature, new_feature,
						 old_lock, new_lock, 0);
			return -EPERM;
		}
	}
	/* nothing invalid, do the changes */
	for (i = 0; i <= AUDIT_LAST_FEATURE; i++) {
		u32 feature = AUDIT_FEATURE_TO_MASK(i);
		u32 old_feature, new_feature, old_lock, new_lock;

		/* if we are not changing this feature, move along */
		if (!(feature & uaf->mask))
			continue;

		old_feature = af.features & feature;
		new_feature = uaf->features & feature;
		old_lock = af.lock & feature;
		new_lock = (uaf->lock | af.lock) & feature;

		if (new_feature != old_feature)
			audit_log_feature_change(i, old_feature, new_feature,
						 old_lock, new_lock, 1);

		if (new_feature)
			af.features |= feature;
		else
			af.features &= ~feature;
		af.lock |= new_lock;
	}

	return 0;
}