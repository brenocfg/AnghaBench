#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ from; scalar_t__ to; } ;
typedef  TYPE_1__ RGraphEdge ;

/* Variables and functions */

__attribute__((used)) static int find_edge(const RGraphEdge *a, const RGraphEdge *b) {
	return a->from == b->to && a->to == b->from? 0: 1;
}