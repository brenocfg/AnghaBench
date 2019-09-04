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
typedef  int /*<<< orphan*/  RCore ;
typedef  int /*<<< orphan*/  RAnalFunction ;
typedef  int /*<<< orphan*/  RAGraph ;

/* Variables and functions */
 int /*<<< orphan*/  r_agraph_reset (int /*<<< orphan*/ *) ; 
 int reload_nodes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int agraph_reload_nodes(RAGraph *g, RCore *core, RAnalFunction *fcn) {
	r_agraph_reset (g);

	return reload_nodes (g, core, fcn);
}