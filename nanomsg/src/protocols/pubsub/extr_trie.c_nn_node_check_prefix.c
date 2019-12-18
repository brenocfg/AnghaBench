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
typedef  scalar_t__ uint8_t ;
struct nn_trie_node {int prefix_len; scalar_t__ const* prefix; } ;

/* Variables and functions */

int nn_node_check_prefix (struct nn_trie_node *self,
    const uint8_t *data, size_t size)
{
    /*  Check how many characters from the data match the prefix. */

    int i;

    for (i = 0; i != self->prefix_len; ++i) {
        if (!size || self->prefix [i] != *data)
            return i;
        ++data;
        --size;
    }
    return self->prefix_len;
}