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
struct lbuf {struct lbuf* l_freelist; int /*<<< orphan*/ * l_wqnext; struct jfs_log* l_log; } ;
struct jfs_log {int /*<<< orphan*/  free_wait; struct lbuf* lbuf_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lbmfree(struct lbuf * bp)
{
	struct jfs_log *log = bp->l_log;

	assert(bp->l_wqnext == NULL);

	/*
	 * return the buffer to head of freelist
	 */
	bp->l_freelist = log->lbuf_free;
	log->lbuf_free = bp;

	wake_up(&log->free_wait);
	return;
}