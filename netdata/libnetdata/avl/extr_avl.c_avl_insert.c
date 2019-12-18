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
struct TYPE_9__ {scalar_t__ avl_balance; struct TYPE_9__** avl_link; } ;
typedef  TYPE_2__ avl ;

/* Variables and functions */
 int AVL_MAX_HEIGHT ; 
 int stub1 (TYPE_2__*,TYPE_2__*) ; 

avl *avl_insert(avl_tree *tree, avl *item) {
    avl *y, *z; /* Top node to update balance factor, and parent. */
    avl *p, *q; /* Iterator, and parent. */
    avl *n;     /* Newly inserted node. */
    avl *w;     /* New root of rebalanced subtree. */
    unsigned char dir; /* Direction to descend. */

    unsigned char da[AVL_MAX_HEIGHT]; /* Cached comparison results. */
    int k = 0;              /* Number of cached results. */

    // assert(tree != NULL && item != NULL);

    z = (avl *) &tree->root;
    y = tree->root;
    dir = 0;
    for (q = z, p = y; p != NULL; q = p, p = p->avl_link[dir]) {
        int cmp = tree->compar(item, p);
        if (cmp == 0)
            return p;

        if (p->avl_balance != 0)
            z = q, y = p, k = 0;
        da[k++] = dir = (unsigned char)(cmp > 0);
    }

    n = q->avl_link[dir] = item;

    // tree->avl_count++;
    n->avl_link[0] = n->avl_link[1] = NULL;
    n->avl_balance = 0;
    if (y == NULL) return n;

    for (p = y, k = 0; p != n; p = p->avl_link[da[k]], k++)
        if (da[k] == 0)
            p->avl_balance--;
        else
            p->avl_balance++;

    if (y->avl_balance == -2) {
        avl *x = y->avl_link[0];
        if (x->avl_balance == -1) {
            w = x;
            y->avl_link[0] = x->avl_link[1];
            x->avl_link[1] = y;
            x->avl_balance = y->avl_balance = 0;
        }
        else {
            // assert (x->avl_balance == +1);
            w = x->avl_link[1];
            x->avl_link[1] = w->avl_link[0];
            w->avl_link[0] = x;
            y->avl_link[0] = w->avl_link[1];
            w->avl_link[1] = y;
            if (w->avl_balance == -1)
                x->avl_balance = 0, y->avl_balance = +1;
            else if (w->avl_balance == 0)
                x->avl_balance = y->avl_balance = 0;
            else /* |w->avl_balance == +1| */
                x->avl_balance = -1, y->avl_balance = 0;
            w->avl_balance = 0;
        }
    }
    else if (y->avl_balance == +2) {
        avl *x = y->avl_link[1];
        if (x->avl_balance == +1) {
            w = x;
            y->avl_link[1] = x->avl_link[0];
            x->avl_link[0] = y;
            x->avl_balance = y->avl_balance = 0;
        }
        else {
            // assert (x->avl_balance == -1);
            w = x->avl_link[0];
            x->avl_link[0] = w->avl_link[1];
            w->avl_link[1] = x;
            y->avl_link[1] = w->avl_link[0];
            w->avl_link[0] = y;
            if (w->avl_balance == +1)
                x->avl_balance = 0, y->avl_balance = -1;
            else if (w->avl_balance == 0)
                x->avl_balance = y->avl_balance = 0;
            else /* |w->avl_balance == -1| */
                x->avl_balance = +1, y->avl_balance = 0;
            w->avl_balance = 0;
        }
    }
    else return n;

    z->avl_link[y != z->avl_link[0]] = w;

    // tree->avl_generation++;
    return n;
}