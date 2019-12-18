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
struct afs_fs_cursor {int flags; int /*<<< orphan*/  type; } ;
struct afs_call {int intr; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int AFS_FS_CURSOR_INTR ; 

__attribute__((used)) static inline void afs_set_fc_call(struct afs_call *call, struct afs_fs_cursor *fc)
{
	call->intr = fc->flags & AFS_FS_CURSOR_INTR;
	fc->type = call->type;
}