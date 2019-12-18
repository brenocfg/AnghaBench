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
struct callchain_node {int count; int children_count; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned callchain_cumul_counts(struct callchain_node *node)
{
	return node->count + node->children_count;
}