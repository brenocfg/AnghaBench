#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct metronomefb_par {size_t dt; TYPE_1__* board; TYPE_2__* metromem_cmd; } ;
struct TYPE_6__ {int /*<<< orphan*/  config; } ;
struct TYPE_5__ {int csum; int opcode; int /*<<< orphan*/ * args; } ;
struct TYPE_4__ {int (* met_wait_event ) (struct metronomefb_par*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ calc_img_cksum (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* epd_frame_table ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct metronomefb_par*) ; 

__attribute__((used)) static int metronome_config_cmd(struct metronomefb_par *par)
{
	/* setup config command
	we can't immediately set the opcode since the controller
	will try parse the command before we've set it all up */

	memcpy(par->metromem_cmd->args, epd_frame_table[par->dt].config,
		sizeof(epd_frame_table[par->dt].config));
	/* the rest are 0 */
	memset(&par->metromem_cmd->args[4], 0,
	       (ARRAY_SIZE(par->metromem_cmd->args) - 4) * 2);

	par->metromem_cmd->csum = 0xCC10;
	par->metromem_cmd->csum += calc_img_cksum(par->metromem_cmd->args, 4);
	par->metromem_cmd->opcode = 0xCC10; /* config cmd */

	return par->board->met_wait_event(par);
}