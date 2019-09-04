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
struct bpf_lru_node {int ref; } ;

/* Variables and functions */

__attribute__((used)) static inline void bpf_lru_node_set_ref(struct bpf_lru_node *node)
{
	/* ref is an approximation on access frequency.  It does not
	 * have to be very accurate.  Hence, no protection is used.
	 */
	if (!node->ref)
		node->ref = 1;
}