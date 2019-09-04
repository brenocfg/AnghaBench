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
typedef  int u16 ;
struct broadsheetfb_par {int /*<<< orphan*/  io_lock; TYPE_3__* board; TYPE_2__* info; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* wait_for_rdy ) (struct broadsheetfb_par*) ;} ;
struct TYPE_4__ {int xres; } ;
struct TYPE_5__ {TYPE_1__ var; scalar_t__ screen_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BS_CMD_LD_IMG_AREA ; 
 int /*<<< orphan*/  BS_CMD_LD_IMG_END ; 
 int /*<<< orphan*/  BS_CMD_UPD_FULL ; 
 int /*<<< orphan*/  BS_CMD_WAIT_DSPE_FREND ; 
 int /*<<< orphan*/  BS_CMD_WAIT_DSPE_TRG ; 
 int /*<<< orphan*/  BS_CMD_WR_REG ; 
 int /*<<< orphan*/  broadsheet_burst_write (struct broadsheetfb_par*,int,int*) ; 
 int /*<<< orphan*/  broadsheet_send_cmdargs (struct broadsheetfb_par*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  broadsheet_send_command (struct broadsheetfb_par*,int /*<<< orphan*/ ) ; 
 int cpu_to_le16 (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct broadsheetfb_par*) ; 

__attribute__((used)) static void broadsheetfb_dpy_update_pages(struct broadsheetfb_par *par,
						u16 y1, u16 y2)
{
	u16 args[5];
	unsigned char *buf = (unsigned char *)par->info->screen_base;

	mutex_lock(&(par->io_lock));
	/* y1 must be a multiple of 4 so drop the lower bits */
	y1 &= 0xFFFC;
	/* y2 must be a multiple of 4 , but - 1 so up the lower bits */
	y2 |= 0x0003;

	args[0] = 0x3 << 4;
	args[1] = 0;
	args[2] = y1;
	args[3] = cpu_to_le16(par->info->var.xres);
	args[4] = y2;
	broadsheet_send_cmdargs(par, BS_CMD_LD_IMG_AREA, 5, args);

	args[0] = 0x154;
	broadsheet_send_cmdargs(par, BS_CMD_WR_REG, 1, args);

	buf += y1 * par->info->var.xres;
	broadsheet_burst_write(par, ((1 + y2 - y1) * par->info->var.xres)/2,
				(u16 *) buf);

	broadsheet_send_command(par, BS_CMD_LD_IMG_END);

	args[0] = 0x4300;
	broadsheet_send_cmdargs(par, BS_CMD_UPD_FULL, 1, args);

	broadsheet_send_command(par, BS_CMD_WAIT_DSPE_TRG);

	broadsheet_send_command(par, BS_CMD_WAIT_DSPE_FREND);

	par->board->wait_for_rdy(par);
	mutex_unlock(&(par->io_lock));

}