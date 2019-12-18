#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  cmdrepeat; TYPE_2__* cons; } ;
struct TYPE_6__ {TYPE_1__* context; } ;
struct TYPE_5__ {int breaked; } ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_core_cmd_repeat (TYPE_3__*,int) ; 

__attribute__((used)) static int r_core_cmd_nullcallback(void *data) {
	RCore *core = (RCore*) data;
	if (core->cons->context->breaked) {
		core->cons->context->breaked = false;
		return 0;
	}
	if (!core->cmdrepeat) {
		return 0;
	}
	r_core_cmd_repeat (core, true);
	return 1;
}