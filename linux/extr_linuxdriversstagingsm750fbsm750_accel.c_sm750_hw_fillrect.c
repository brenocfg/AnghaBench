#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct lynx_accel {scalar_t__ (* de_wait ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DE_CONTROL ; 
 int DE_CONTROL_COMMAND_RECTANGLE_FILL ; 
 int DE_CONTROL_LAST_PIXEL ; 
 int DE_CONTROL_ROP_MASK ; 
 int DE_CONTROL_ROP_SELECT ; 
 int DE_CONTROL_STATUS ; 
 int /*<<< orphan*/  DE_DESTINATION ; 
 int DE_DESTINATION_X_MASK ; 
 int DE_DESTINATION_X_SHIFT ; 
 int DE_DESTINATION_Y_MASK ; 
 int /*<<< orphan*/  DE_DIMENSION ; 
 int DE_DIMENSION_X_MASK ; 
 int DE_DIMENSION_X_SHIFT ; 
 int DE_DIMENSION_Y_ET_MASK ; 
 int /*<<< orphan*/  DE_FOREGROUND ; 
 int /*<<< orphan*/  DE_PITCH ; 
 int DE_PITCH_DESTINATION_MASK ; 
 int DE_PITCH_DESTINATION_SHIFT ; 
 int DE_PITCH_SOURCE_MASK ; 
 int /*<<< orphan*/  DE_WINDOW_DESTINATION_BASE ; 
 int /*<<< orphan*/  DE_WINDOW_WIDTH ; 
 int DE_WINDOW_WIDTH_DST_MASK ; 
 int DE_WINDOW_WIDTH_DST_SHIFT ; 
 int DE_WINDOW_WIDTH_SRC_MASK ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  write_dpr (struct lynx_accel*,int /*<<< orphan*/ ,int) ; 

int sm750_hw_fillrect(struct lynx_accel *accel,
		      u32 base, u32 pitch, u32 Bpp,
		      u32 x, u32 y, u32 width, u32 height,
		      u32 color, u32 rop)
{
	u32 deCtrl;

	if (accel->de_wait() != 0) {
		/*
		 * int time wait and always busy,seems hardware
		 * got something error
		 */
		pr_debug("De engine always busy\n");
		return -1;
	}

	write_dpr(accel, DE_WINDOW_DESTINATION_BASE, base); /* dpr40 */
	write_dpr(accel, DE_PITCH,
		  ((pitch / Bpp << DE_PITCH_DESTINATION_SHIFT) &
		   DE_PITCH_DESTINATION_MASK) |
		  (pitch / Bpp & DE_PITCH_SOURCE_MASK)); /* dpr10 */

	write_dpr(accel, DE_WINDOW_WIDTH,
		  ((pitch / Bpp << DE_WINDOW_WIDTH_DST_SHIFT) &
		   DE_WINDOW_WIDTH_DST_MASK) |
		   (pitch / Bpp & DE_WINDOW_WIDTH_SRC_MASK)); /* dpr44 */

	write_dpr(accel, DE_FOREGROUND, color); /* DPR14 */

	write_dpr(accel, DE_DESTINATION,
		  ((x << DE_DESTINATION_X_SHIFT) & DE_DESTINATION_X_MASK) |
		  (y & DE_DESTINATION_Y_MASK)); /* dpr4 */

	write_dpr(accel, DE_DIMENSION,
		  ((width << DE_DIMENSION_X_SHIFT) & DE_DIMENSION_X_MASK) |
		  (height & DE_DIMENSION_Y_ET_MASK)); /* dpr8 */

	deCtrl = DE_CONTROL_STATUS | DE_CONTROL_LAST_PIXEL |
		DE_CONTROL_COMMAND_RECTANGLE_FILL | DE_CONTROL_ROP_SELECT |
		(rop & DE_CONTROL_ROP_MASK); /* dpr0xc */

	write_dpr(accel, DE_CONTROL, deCtrl);
	return 0;
}