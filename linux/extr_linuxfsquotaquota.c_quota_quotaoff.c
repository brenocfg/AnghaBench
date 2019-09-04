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
struct super_block {TYPE_1__* s_qcop; } ;
struct TYPE_2__ {int (* quota_off ) (struct super_block*,int) ;int (* quota_disable ) (struct super_block*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  qtype_enforce_flag (int) ; 
 int stub1 (struct super_block*,int /*<<< orphan*/ ) ; 
 int stub2 (struct super_block*,int) ; 

__attribute__((used)) static int quota_quotaoff(struct super_block *sb, int type)
{
	if (!sb->s_qcop->quota_off && !sb->s_qcop->quota_disable)
		return -ENOSYS;
	if (sb->s_qcop->quota_disable)
		return sb->s_qcop->quota_disable(sb, qtype_enforce_flag(type));
	return sb->s_qcop->quota_off(sb, type);
}