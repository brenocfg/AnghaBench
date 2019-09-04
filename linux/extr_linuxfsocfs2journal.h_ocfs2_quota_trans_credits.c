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

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_FEATURE_RO_COMPAT_GRPQUOTA ; 
 int /*<<< orphan*/  OCFS2_FEATURE_RO_COMPAT_USRQUOTA ; 
 scalar_t__ OCFS2_HAS_RO_COMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ OCFS2_QWRITE_CREDITS ; 

__attribute__((used)) static inline int ocfs2_quota_trans_credits(struct super_block *sb)
{
	int credits = 0;

	if (OCFS2_HAS_RO_COMPAT_FEATURE(sb, OCFS2_FEATURE_RO_COMPAT_USRQUOTA))
		credits += OCFS2_QWRITE_CREDITS;
	if (OCFS2_HAS_RO_COMPAT_FEATURE(sb, OCFS2_FEATURE_RO_COMPAT_GRPQUOTA))
		credits += OCFS2_QWRITE_CREDITS;
	return credits;
}