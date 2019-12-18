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
struct nn_trie_node {int dummy; } ;

/* Variables and functions */

struct nn_trie_node **nn_node_child (struct nn_trie_node *self, int index)
{
    /*  Finds pointer to the n-th child of the node. */

    return ((struct nn_trie_node**) (self + 1)) + index;
}