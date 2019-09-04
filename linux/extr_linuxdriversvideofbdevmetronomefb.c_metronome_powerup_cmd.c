#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct metronomefb_par {TYPE_2__* board; TYPE_1__* metromem_cmd; } ;
struct TYPE_4__ {int (* met_wait_event ) (struct metronomefb_par*) ;int /*<<< orphan*/  (* set_stdby ) (struct metronomefb_par*,int) ;int /*<<< orphan*/  (* set_rst ) (struct metronomefb_par*,int) ;} ;
struct TYPE_3__ {int opcode; int* args; int csum; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct metronomefb_par*,int) ; 
 int /*<<< orphan*/  stub2 (struct metronomefb_par*,int) ; 
 int stub3 (struct metronomefb_par*) ; 

__attribute__((used)) static int metronome_powerup_cmd(struct metronomefb_par *par)
{
	int i;
	u16 cs;

	/* setup power up command */
	par->metromem_cmd->opcode = 0x1234; /* pwr up pseudo cmd */
	cs = par->metromem_cmd->opcode;

	/* set pwr1,2,3 to 1024 */
	for (i = 0; i < 3; i++) {
		par->metromem_cmd->args[i] = 1024;
		cs += par->metromem_cmd->args[i];
	}

	/* the rest are 0 */
	memset(&par->metromem_cmd->args[i], 0,
	       (ARRAY_SIZE(par->metromem_cmd->args) - i) * 2);

	par->metromem_cmd->csum = cs;

	msleep(1);
	par->board->set_rst(par, 1);

	msleep(1);
	par->board->set_stdby(par, 1);

	return par->board->met_wait_event(par);
}