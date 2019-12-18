#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rwlock; int /*<<< orphan*/  mutex; int /*<<< orphan*/  avl_tree; } ;
typedef  TYPE_1__ avl_tree_lock ;

/* Variables and functions */
 int /*<<< orphan*/  avl_init (int /*<<< orphan*/ *,int (*) (void*,void*)) ; 
 int /*<<< orphan*/  fatal (char*,int) ; 
 int netdata_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int netdata_rwlock_init (int /*<<< orphan*/ *) ; 

void avl_init_lock(avl_tree_lock *tree, int (*compar)(void * /*a*/, void * /*b*/)) {
    avl_init(&tree->avl_tree, compar);

#ifndef AVL_WITHOUT_PTHREADS
    int lock;

#ifdef AVL_LOCK_WITH_MUTEX
    lock = netdata_mutex_init(&tree->mutex, NULL);
#else
    lock = netdata_rwlock_init(&tree->rwlock);
#endif

    if(lock != 0)
        fatal("Failed to initialize AVL mutex/rwlock, error: %d", lock);

#endif /* AVL_WITHOUT_PTHREADS */
}