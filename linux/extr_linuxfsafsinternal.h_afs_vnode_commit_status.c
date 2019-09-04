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
struct afs_vnode {int dummy; } ;
struct TYPE_2__ {scalar_t__ error; } ;
struct afs_fs_cursor {int /*<<< orphan*/  key; TYPE_1__ ac; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_cache_permit (struct afs_vnode*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void afs_vnode_commit_status(struct afs_fs_cursor *fc,
					   struct afs_vnode *vnode,
					   unsigned int cb_break)
{
	if (fc->ac.error == 0)
		afs_cache_permit(vnode, fc->key, cb_break);
}