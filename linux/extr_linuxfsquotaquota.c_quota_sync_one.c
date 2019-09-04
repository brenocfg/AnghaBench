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
struct super_block {int s_quota_types; TYPE_1__* s_qcop; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* quota_sync ) (struct super_block*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct super_block*,int) ; 

__attribute__((used)) static void quota_sync_one(struct super_block *sb, void *arg)
{
	int type = *(int *)arg;

	if (sb->s_qcop && sb->s_qcop->quota_sync &&
	    (sb->s_quota_types & (1 << type)))
		sb->s_qcop->quota_sync(sb, type);
}