#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int is_callgraph; } ;
typedef  int /*<<< orphan*/  RCore ;
typedef  int /*<<< orphan*/  RAnalFunction ;
typedef  TYPE_1__ RAGraph ;

/* Variables and functions */
 int get_bbnodes (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_cgnodes (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reload_nodes(RAGraph *g, RCore *core, RAnalFunction *fcn) {
	int is_c = g->is_callgraph;
	return is_c? get_cgnodes (g, core, fcn): get_bbnodes (g, core, fcn);
}