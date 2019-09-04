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
typedef  int u8 ;
struct TYPE_4__ {TYPE_1__* extif; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_data ) (int*,int) ;int /*<<< orphan*/  (* write_command ) (int*,int) ;int /*<<< orphan*/  (* set_bits_per_cycle ) (int) ;} ;

/* Variables and functions */
 int HWA742_WINDOW_X_START_0 ; 
 TYPE_2__ hwa742 ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int*,int) ; 
 int /*<<< orphan*/  stub3 (int*,int) ; 

__attribute__((used)) static void set_window_regs(int x_start, int y_start, int x_end, int y_end)
{
	u8 tmp[8];
	u8 cmd;

	x_end--;
	y_end--;
	tmp[0] = x_start;
	tmp[1] = x_start >> 8;
	tmp[2] = y_start;
	tmp[3] = y_start >> 8;
	tmp[4] = x_end;
	tmp[5] = x_end >> 8;
	tmp[6] = y_end;
	tmp[7] = y_end >> 8;

	hwa742.extif->set_bits_per_cycle(8);
	cmd = HWA742_WINDOW_X_START_0;

	hwa742.extif->write_command(&cmd, 1);

	hwa742.extif->write_data(tmp, 8);
}