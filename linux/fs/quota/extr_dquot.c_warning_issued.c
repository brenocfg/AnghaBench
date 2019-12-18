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
struct dquot {int /*<<< orphan*/  dq_flags; } ;

/* Variables and functions */
 int DQ_BLKS_B ; 
 int DQ_INODES_B ; 
 int const QUOTA_NL_BHARDWARN ; 
 int const QUOTA_NL_BSOFTLONGWARN ; 
 int const QUOTA_NL_IHARDWARN ; 
 int const QUOTA_NL_ISOFTLONGWARN ; 
 int test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int warning_issued(struct dquot *dquot, const int warntype)
{
	int flag = (warntype == QUOTA_NL_BHARDWARN ||
		warntype == QUOTA_NL_BSOFTLONGWARN) ? DQ_BLKS_B :
		((warntype == QUOTA_NL_IHARDWARN ||
		warntype == QUOTA_NL_ISOFTLONGWARN) ? DQ_INODES_B : 0);

	if (!flag)
		return 0;
	return test_and_set_bit(flag, &dquot->dq_flags);
}