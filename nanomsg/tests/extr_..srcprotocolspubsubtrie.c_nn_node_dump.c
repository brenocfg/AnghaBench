#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int min; int max; scalar_t__ nbr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * children; } ;
struct TYPE_6__ {TYPE_2__ dense; TYPE_1__ sparse; } ;
struct nn_trie_node {int prefix_len; int type; TYPE_3__ u; int /*<<< orphan*/ * prefix; scalar_t__ refcount; } ;

/* Variables and functions */
 int NN_TRIE_DENSE_TYPE ; 
 int /*<<< orphan*/  nn_node_indent (int) ; 
 int /*<<< orphan*/  nn_node_putchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void nn_node_dump (struct nn_trie_node *self, int indent)
{
    int i;
    int children;

    if (!self) {
        nn_node_indent (indent);
        printf ("NULL\n");
        return;
    }

    nn_node_indent (indent);
    printf ("===================\n");
    nn_node_indent (indent);
    printf ("refcount=%d\n", (int) self->refcount);
    nn_node_indent (indent);
    printf ("prefix_len=%d\n", (int) self->prefix_len);
    nn_node_indent (indent);
    if (self->type == NN_TRIE_DENSE_TYPE)
        printf ("type=dense\n");
    else
        printf ("type=sparse\n");
    nn_node_indent (indent);
    printf ("prefix=\"");
    for (i = 0; i != self->prefix_len; ++i)
        nn_node_putchar (self->prefix [i]);
    printf ("\"\n");
    if (self->type <= 8) {
        nn_node_indent (indent);
        printf ("sparse.children=\"");
        for (i = 0; i != self->type; ++i)
            nn_node_putchar (self->u.sparse.children [i]);
        printf ("\"\n");
        children = self->type;
    }
    else {
        nn_node_indent (indent);
        printf ("dense.min='%c' (%d)\n", (char) self->u.dense.min,
            (int) self->u.dense.min);
        nn_node_indent (indent);
        printf ("dense.max='%c' (%d)\n", (char) self->u.dense.max,
            (int) self->u.dense.max);
        nn_node_indent (indent);
        printf ("dense.nbr=%d\n", (int) self->u.dense.nbr);
        children = self->u.dense.max - self->u.dense.min + 1;
    }

    for (i = 0; i != children; ++i)
        nn_node_dump (((struct nn_trie_node**) (self + 1)) [i], indent + 1);

    nn_node_indent (indent);
    printf ("===================\n");
}