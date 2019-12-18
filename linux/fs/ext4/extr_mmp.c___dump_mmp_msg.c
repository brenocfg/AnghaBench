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
struct mmp_struct {int /*<<< orphan*/  mmp_bdevname; int /*<<< orphan*/  mmp_nodename; int /*<<< orphan*/  mmp_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ext4_warning (struct super_block*,char const*,unsigned int,char*,...) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 

void __dump_mmp_msg(struct super_block *sb, struct mmp_struct *mmp,
		    const char *function, unsigned int line, const char *msg)
{
	__ext4_warning(sb, function, line, "%s", msg);
	__ext4_warning(sb, function, line,
		       "MMP failure info: last update time: %llu, last update "
		       "node: %s, last update device: %s",
		       (long long unsigned int) le64_to_cpu(mmp->mmp_time),
		       mmp->mmp_nodename, mmp->mmp_bdevname);
}