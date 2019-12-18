#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int is_tiny; int zoom; int need_update_dim; int need_set_layout; TYPE_1__* can; int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {int sy; } ;
typedef  TYPE_2__ RAGraph ;

/* Variables and functions */
 int /*<<< orphan*/  R_AGRAPH_MODE_MINI ; 
 int /*<<< orphan*/  R_AGRAPH_MODE_NORMAL ; 
 int /*<<< orphan*/  R_AGRAPH_MODE_TINY ; 

__attribute__((used)) static void agraph_set_zoom(RAGraph *g, int v) {
	if (v >= -10) {
		g->is_tiny = false;
		if (v == 0) {
			g->mode = R_AGRAPH_MODE_MINI;
		} else if (v < 0) {
			g->mode = R_AGRAPH_MODE_TINY;
			g->is_tiny = true;
		} else {
			g->mode = R_AGRAPH_MODE_NORMAL;
		}
		const int K = 920;
		if (g->zoom < v) {
			g->can->sy = (g->can->sy * K) / 1000;
		}
		else {
			g->can->sy = (g->can->sy * 1000) / K;
		}
		g->zoom = v;
		g->need_update_dim = true;
		g->need_set_layout = true;
	}
}