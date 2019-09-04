#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  anal; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ RSignGraph ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  parseGraphMetrics (char const*,int,TYPE_1__*) ; 
 int r_sign_add_graph (int /*<<< orphan*/ ,char const*,TYPE_1__) ; 

__attribute__((used)) static bool addGraphZign(RCore *core, const char *name, const char *args0, int nargs) {
	RSignGraph graph = {0};
	if (!parseGraphMetrics (args0, nargs, &graph)) {
		eprintf ("error: invalid arguments\n");
		return false;
	}
	return r_sign_add_graph (core->anal, name, graph);
}