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
struct aty128fb_par {int dummy; } ;

/* Variables and functions */
 int PC_BUSY ; 
 int /*<<< orphan*/  PC_NGUI_CTLSTAT ; 
 int aty_ld_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aty128_flush_pixel_cache(const struct aty128fb_par *par)
{
	int i;
	u32 tmp;

	tmp = aty_ld_le32(PC_NGUI_CTLSTAT);
	tmp &= ~(0x00ff);
	tmp |= 0x00ff;
	aty_st_le32(PC_NGUI_CTLSTAT, tmp);

	for (i = 0; i < 2000000; i++)
		if (!(aty_ld_le32(PC_NGUI_CTLSTAT) & PC_BUSY))
			break;
}