#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  avl_tree; } ;
typedef  TYPE_1__ avl_tree_lock ;

/* Variables and functions */
 int /*<<< orphan*/  avl_read_lock (TYPE_1__*) ; 
 int avl_traverse (int /*<<< orphan*/ *,int (*) (void*,void*),void*) ; 
 int /*<<< orphan*/  avl_unlock (TYPE_1__*) ; 

int avl_traverse_lock(avl_tree_lock *tree, int (*callback)(void * /*entry*/, void * /*data*/), void *data) {
    int ret;
    avl_read_lock(tree);
    ret = avl_traverse(&tree->avl_tree, callback, data);
    avl_unlock(tree);
    return ret;
}