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
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct list_head*) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memalloc_nofs_restore (unsigned int) ; 
 unsigned int memalloc_nofs_save () ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  wait ; 
 TYPE_1__ wsm ; 
 struct list_head* zstd_alloc_workspace (unsigned int) ; 
 struct list_head* zstd_find_workspace (unsigned int) ; 

__attribute__((used)) static struct list_head *zstd_get_workspace(unsigned int level)
{
	struct list_head *ws;
	unsigned int nofs_flag;

	/* level == 0 means we can use any workspace */
	if (!level)
		level = 1;

again:
	ws = zstd_find_workspace(level);
	if (ws)
		return ws;

	nofs_flag = memalloc_nofs_save();
	ws = zstd_alloc_workspace(level);
	memalloc_nofs_restore(nofs_flag);

	if (IS_ERR(ws)) {
		DEFINE_WAIT(wait);

		prepare_to_wait(&wsm.wait, &wait, TASK_UNINTERRUPTIBLE);
		schedule();
		finish_wait(&wsm.wait, &wait);

		goto again;
	}

	return ws;
}