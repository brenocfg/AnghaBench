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
struct super_block {int dummy; } ;
struct quota_info {TYPE_1__** ops; } ;
struct TYPE_2__ {int (* write_file_info ) (struct super_block*,int) ;} ;

/* Variables and functions */
 struct quota_info* sb_dqopt (struct super_block*) ; 
 int stub1 (struct super_block*,int) ; 

int dquot_commit_info(struct super_block *sb, int type)
{
	struct quota_info *dqopt = sb_dqopt(sb);

	return dqopt->ops[type]->write_file_info(sb, type);
}