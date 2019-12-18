#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* graph; } ;
struct TYPE_5__ {scalar_t__ cc; scalar_t__ nbbs; scalar_t__ ebbs; scalar_t__ edges; scalar_t__ bbsum; } ;
typedef  TYPE_2__ RSignItem ;

/* Variables and functions */

__attribute__((used)) static bool matchGraph(RSignItem *a, RSignItem *b) {
	if (a->graph && b->graph) {
		if (a->graph->cc != b->graph->cc) {
			return false;
		}
		if (a->graph->nbbs != b->graph->nbbs) {
			return false;
		}
		if (a->graph->ebbs != b->graph->ebbs) {
			return false;
		}
		if (a->graph->edges != b->graph->edges) {
			return false;
		}
		if (a->graph->bbsum!= b->graph->bbsum) {
			return false;
		}
		return true;
	}
	return false;
}