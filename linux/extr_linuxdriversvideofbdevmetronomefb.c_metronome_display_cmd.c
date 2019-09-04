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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u16 ;
struct metronomefb_par {int frame_count; TYPE_2__* board; TYPE_1__* metromem_cmd; } ;
struct TYPE_4__ {int (* met_wait_event_intr ) (struct metronomefb_par*) ;} ;
struct TYPE_3__ {int opcode; int* args; void* csum; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct metronomefb_par*) ; 

__attribute__((used)) static int metronome_display_cmd(struct metronomefb_par *par)
{
	int i;
	u16 cs;
	u16 opcode;
	static u8 borderval;

	/* setup display command
	we can't immediately set the opcode since the controller
	will try parse the command before we've set it all up
	so we just set cs here and set the opcode at the end */

	if (par->metromem_cmd->opcode == 0xCC40)
		opcode = cs = 0xCC41;
	else
		opcode = cs = 0xCC40;

	/* set the args ( 2 bytes ) for display */
	i = 0;
	par->metromem_cmd->args[i] = 	1 << 3 /* border update */
					| ((borderval++ % 4) & 0x0F) << 4
					| (par->frame_count - 1) << 8;
	cs += par->metromem_cmd->args[i++];

	/* the rest are 0 */
	memset((u8 *) (par->metromem_cmd->args + i), 0, (32-i)*2);

	par->metromem_cmd->csum = cs;
	par->metromem_cmd->opcode = opcode; /* display cmd */

	return par->board->met_wait_event_intr(par);
}