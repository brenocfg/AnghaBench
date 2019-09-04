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
struct super_block {int dummy; } ;
struct nilfs_super_block {int /*<<< orphan*/  s_feature_compat_ro; int /*<<< orphan*/  s_feature_incompat; } ;
typedef  int __u64 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int NILFS_FEATURE_COMPAT_RO_SUPP ; 
 int NILFS_FEATURE_INCOMPAT_SUPP ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 

int nilfs_check_feature_compatibility(struct super_block *sb,
				      struct nilfs_super_block *sbp)
{
	__u64 features;

	features = le64_to_cpu(sbp->s_feature_incompat) &
		~NILFS_FEATURE_INCOMPAT_SUPP;
	if (features) {
		nilfs_msg(sb, KERN_ERR,
			  "couldn't mount because of unsupported optional features (%llx)",
			  (unsigned long long)features);
		return -EINVAL;
	}
	features = le64_to_cpu(sbp->s_feature_compat_ro) &
		~NILFS_FEATURE_COMPAT_RO_SUPP;
	if (!sb_rdonly(sb) && features) {
		nilfs_msg(sb, KERN_ERR,
			  "couldn't mount RDWR because of unsupported optional features (%llx)",
			  (unsigned long long)features);
		return -EINVAL;
	}
	return 0;
}