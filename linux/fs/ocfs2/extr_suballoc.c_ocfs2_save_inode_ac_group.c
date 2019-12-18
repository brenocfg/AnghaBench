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
struct ocfs2_alloc_context {int /*<<< orphan*/  ac_alloc_slot; int /*<<< orphan*/  ac_last_group; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_last_used_slot; int /*<<< orphan*/  ip_last_used_group; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 

__attribute__((used)) static inline void ocfs2_save_inode_ac_group(struct inode *dir,
					     struct ocfs2_alloc_context *ac)
{
	OCFS2_I(dir)->ip_last_used_group = ac->ac_last_group;
	OCFS2_I(dir)->ip_last_used_slot = ac->ac_alloc_slot;
}