#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int (* compar ) (TYPE_2__*,TYPE_2__*) ;TYPE_2__* root; } ;
typedef  TYPE_1__ avl_tree ;
struct TYPE_9__ {struct TYPE_9__** avl_link; } ;
typedef  TYPE_2__ avl ;

/* Variables and functions */
 int stub1 (TYPE_2__*,TYPE_2__*) ; 

avl *avl_search(avl_tree *tree, avl *item) {
    avl *p;

    // assert (tree != NULL && item != NULL);

    for (p = tree->root; p != NULL; ) {
        int cmp = tree->compar(item, p);

        if (cmp < 0)
            p = p->avl_link[0];
        else if (cmp > 0)
            p = p->avl_link[1];
        else /* |cmp == 0| */
            return p;
    }

    return NULL;
}