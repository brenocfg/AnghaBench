#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  panels; } ;
struct TYPE_9__ {TYPE_1__* model; } ;
struct TYPE_8__ {int /*<<< orphan*/  rotate; } ;
typedef  TYPE_2__ RPanel ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 TYPE_2__* __get_cur_panel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __rotate_asmemu (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  r_core_visual_applyHexMode (TYPE_3__*,int /*<<< orphan*/ ) ; 

void __rotate_hexdump_cb (void *user, bool rev) {
	RCore *core = (RCore *)user;
	RPanel *p = __get_cur_panel (core->panels);

	if (rev) {
		p->model->rotate--;
	} else {
		p->model->rotate++;
	}
	r_core_visual_applyHexMode (core, p->model->rotate);
	__rotate_asmemu (core, p);
}