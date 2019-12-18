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
struct nn_trie_node {scalar_t__ refcount; } ;

/* Variables and functions */

int nn_node_has_subscribers (struct nn_trie_node *node)
{
    /*  Returns 1 when there are no subscribers associated with the node. */
    return node->refcount ? 1 : 0;
}