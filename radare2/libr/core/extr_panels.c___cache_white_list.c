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
struct TYPE_5__ {TYPE_1__* model; } ;
struct TYPE_4__ {int cache; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_2__ RPanel ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int COUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cache_white_list_cmds ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __cache_white_list(RCore *core, RPanel *panel) {
	int i = 0;
	for (; i < COUNT (cache_white_list_cmds); i++) {
		if (!strcmp (panel->model->cmd, cache_white_list_cmds[i])) {
			panel->model->cache = true;
			return;
		}
	}
	panel->model->cache = false;
}