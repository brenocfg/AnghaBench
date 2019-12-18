#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ len; } ;
struct extent_tree {int largest_updated; TYPE_1__ largest; } ;
struct extent_node {TYPE_1__ ei; } ;

/* Variables and functions */

__attribute__((used)) static inline void __try_update_largest_extent(struct extent_tree *et,
						struct extent_node *en)
{
	if (en->ei.len > et->largest.len) {
		et->largest = en->ei;
		et->largest_updated = true;
	}
}