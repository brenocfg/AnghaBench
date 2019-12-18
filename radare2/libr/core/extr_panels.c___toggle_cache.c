#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* view; TYPE_1__* model; } ;
struct TYPE_7__ {int refresh; } ;
struct TYPE_6__ {int cache; } ;
typedef  TYPE_3__ RPanel ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __set_cmd_str_cache (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 

void __toggle_cache (RCore *core, RPanel *p) {
	p->model->cache = !p->model->cache;
	__set_cmd_str_cache (core, p, NULL);
	p->view->refresh = true;
}