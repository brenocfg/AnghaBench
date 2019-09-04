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
struct TYPE_8__ {int rotate; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_2__ RPanel ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 TYPE_2__* getCurPanel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_visual_applyDisMode (TYPE_3__*,int) ; 
 int /*<<< orphan*/  rotateAsmemu (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void rotateDisasCb(void *user, bool rev) {
	RCore *core = (RCore *)user;
	RPanel *p = getCurPanel (core->panels);

	//TODO: need to come up with a better solution but okay for now
	if (!strcmp (p->model->cmd, "pdc")) {
		return;
	}

	if (rev) {
		if (!p->model->rotate) {
			p->model->rotate = 4;
		} else {
			p->model->rotate--;
		}
	} else {
		p->model->rotate++;
	}
	r_core_visual_applyDisMode (core, p->model->rotate);
	rotateAsmemu (core, p);
}