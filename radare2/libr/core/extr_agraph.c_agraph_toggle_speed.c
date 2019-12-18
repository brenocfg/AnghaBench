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
struct TYPE_6__ {int movspeed; } ;
struct TYPE_5__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RAGraph ;

/* Variables and functions */
 int const DEFAULT_SPEED ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void agraph_toggle_speed(RAGraph *g, RCore *core) {
	const int alt = r_config_get_i (core->config, "graph.scroll");
	g->movspeed = g->movspeed == DEFAULT_SPEED? alt: DEFAULT_SPEED;
}