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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int type; int /*<<< orphan*/  cookie; scalar_t__ flags; scalar_t__ list; scalar_t__ pad1; int /*<<< orphan*/  node; void* highest_blocked; void* convert_type; } ;
struct dlm_lock {int /*<<< orphan*/  lock_refs; scalar_t__ lksb_kernel_allocated; scalar_t__ cancel_pending; scalar_t__ unlock_pending; scalar_t__ lock_pending; scalar_t__ convert_pending; scalar_t__ bast_pending; scalar_t__ ast_pending; TYPE_1__ ml; int /*<<< orphan*/ * astdata; int /*<<< orphan*/ * bast; int /*<<< orphan*/ * ast; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  bast_list; int /*<<< orphan*/  ast_list; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* LKM_IVMODE ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_init_lock(struct dlm_lock *newlock, int type,
			  u8 node, u64 cookie)
{
	INIT_LIST_HEAD(&newlock->list);
	INIT_LIST_HEAD(&newlock->ast_list);
	INIT_LIST_HEAD(&newlock->bast_list);
	spin_lock_init(&newlock->spinlock);
	newlock->ml.type = type;
	newlock->ml.convert_type = LKM_IVMODE;
	newlock->ml.highest_blocked = LKM_IVMODE;
	newlock->ml.node = node;
	newlock->ml.pad1 = 0;
	newlock->ml.list = 0;
	newlock->ml.flags = 0;
	newlock->ast = NULL;
	newlock->bast = NULL;
	newlock->astdata = NULL;
	newlock->ml.cookie = cpu_to_be64(cookie);
	newlock->ast_pending = 0;
	newlock->bast_pending = 0;
	newlock->convert_pending = 0;
	newlock->lock_pending = 0;
	newlock->unlock_pending = 0;
	newlock->cancel_pending = 0;
	newlock->lksb_kernel_allocated = 0;

	kref_init(&newlock->lock_refs);
}