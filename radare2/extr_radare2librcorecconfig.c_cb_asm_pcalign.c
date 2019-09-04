#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int i_value; } ;
struct TYPE_7__ {TYPE_2__* anal; TYPE_1__* assembler; } ;
struct TYPE_6__ {int pcalign; } ;
struct TYPE_5__ {int pcalign; } ;
typedef  TYPE_3__ RCore ;
typedef  TYPE_4__ RConfigNode ;

/* Variables and functions */

__attribute__((used)) static int cb_asm_pcalign(void *user, void *data) {
	RCore *core = (RCore *) user;
	RConfigNode *node = (RConfigNode *) data;
	int align = node->i_value;
	if (align < 0) {
		align = 0;
	}
	core->assembler->pcalign = align;
	core->anal->pcalign = align;
	return true;
}