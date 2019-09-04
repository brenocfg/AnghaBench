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
typedef  int u32 ;
struct radeonfb_info {int bpp; int depth; TYPE_2__* info; TYPE_1__* palette; int /*<<< orphan*/  asleep; } ;
struct TYPE_4__ {int* pseudo_palette; } ;
struct TYPE_3__ {unsigned int red; unsigned int green; unsigned int blue; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  PALETTE_DATA ; 
 int /*<<< orphan*/  PALETTE_INDEX ; 
 int /*<<< orphan*/  radeon_fifo_wait (int) ; 

__attribute__((used)) static int radeon_setcolreg (unsigned regno, unsigned red, unsigned green,
                             unsigned blue, unsigned transp,
			     struct radeonfb_info *rinfo)
{
	u32 pindex;
	unsigned int i;


	if (regno > 255)
		return -EINVAL;

	red >>= 8;
	green >>= 8;
	blue >>= 8;
	rinfo->palette[regno].red = red;
	rinfo->palette[regno].green = green;
	rinfo->palette[regno].blue = blue;

        /* default */
        pindex = regno;

        if (!rinfo->asleep) {
		radeon_fifo_wait(9);

		if (rinfo->bpp == 16) {
			pindex = regno * 8;

			if (rinfo->depth == 16 && regno > 63)
				return -EINVAL;
			if (rinfo->depth == 15 && regno > 31)
				return -EINVAL;

			/* For 565, the green component is mixed one order
			 * below
			 */
			if (rinfo->depth == 16) {
		                OUTREG(PALETTE_INDEX, pindex>>1);
	       	         	OUTREG(PALETTE_DATA,
				       (rinfo->palette[regno>>1].red << 16) |
	                        	(green << 8) |
				       (rinfo->palette[regno>>1].blue));
	                	green = rinfo->palette[regno<<1].green;
	        	}
		}

		if (rinfo->depth != 16 || regno < 32) {
			OUTREG(PALETTE_INDEX, pindex);
			OUTREG(PALETTE_DATA, (red << 16) |
			       (green << 8) | blue);
		}
	}
 	if (regno < 16) {
		u32 *pal = rinfo->info->pseudo_palette;
        	switch (rinfo->depth) {
		case 15:
			pal[regno] = (regno << 10) | (regno << 5) | regno;
			break;
		case 16:
			pal[regno] = (regno << 11) | (regno << 5) | regno;
			break;
		case 24:
			pal[regno] = (regno << 16) | (regno << 8) | regno;
			break;
		case 32:
			i = (regno << 8) | regno;
			pal[regno] = (i << 16) | i;
			break;
		}
        }
	return 0;
}