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
typedef  int u64 ;
struct btrfs_feature_attr {int feature_set; int feature_bit; } ;

/* Variables and functions */
 int BTRFS_FEATURE_COMPAT_RO_SAFE_CLEAR ; 
 int BTRFS_FEATURE_COMPAT_RO_SAFE_SET ; 
 int BTRFS_FEATURE_COMPAT_SAFE_CLEAR ; 
 int BTRFS_FEATURE_COMPAT_SAFE_SET ; 
 int BTRFS_FEATURE_INCOMPAT_SAFE_CLEAR ; 
 int BTRFS_FEATURE_INCOMPAT_SAFE_SET ; 
#define  FEAT_COMPAT 130 
#define  FEAT_COMPAT_RO 129 
#define  FEAT_INCOMPAT 128 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static int can_modify_feature(struct btrfs_feature_attr *fa)
{
	int val = 0;
	u64 set, clear;
	switch (fa->feature_set) {
	case FEAT_COMPAT:
		set = BTRFS_FEATURE_COMPAT_SAFE_SET;
		clear = BTRFS_FEATURE_COMPAT_SAFE_CLEAR;
		break;
	case FEAT_COMPAT_RO:
		set = BTRFS_FEATURE_COMPAT_RO_SAFE_SET;
		clear = BTRFS_FEATURE_COMPAT_RO_SAFE_CLEAR;
		break;
	case FEAT_INCOMPAT:
		set = BTRFS_FEATURE_INCOMPAT_SAFE_SET;
		clear = BTRFS_FEATURE_INCOMPAT_SAFE_CLEAR;
		break;
	default:
		pr_warn("btrfs: sysfs: unknown feature set %d\n",
				fa->feature_set);
		return 0;
	}

	if (set & fa->feature_bit)
		val |= 1;
	if (clear & fa->feature_bit)
		val |= 2;

	return val;
}