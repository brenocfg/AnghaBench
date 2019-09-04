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
struct fuse_iqueue {int connected; int /*<<< orphan*/  forget_list_head; int /*<<< orphan*/ * forget_list_tail; int /*<<< orphan*/  interrupts; int /*<<< orphan*/  pending; int /*<<< orphan*/  waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct fuse_iqueue*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fuse_iqueue_init(struct fuse_iqueue *fiq)
{
	memset(fiq, 0, sizeof(struct fuse_iqueue));
	init_waitqueue_head(&fiq->waitq);
	INIT_LIST_HEAD(&fiq->pending);
	INIT_LIST_HEAD(&fiq->interrupts);
	fiq->forget_list_tail = &fiq->forget_list_head;
	fiq->connected = 1;
}