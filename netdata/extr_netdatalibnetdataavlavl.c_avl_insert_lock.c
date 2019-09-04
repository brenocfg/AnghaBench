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
typedef  int /*<<< orphan*/  avl ;

/* Variables and functions */
 int /*<<< orphan*/ * avl_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  avl_write_lock (TYPE_1__*) ; 

avl *avl_insert_lock(avl_tree_lock *tree, avl *item) {
    avl_write_lock(tree);
    avl * ret = avl_insert(&tree->avl_tree, item);
    avl_unlock(tree);
    return ret;
}