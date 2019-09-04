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
typedef  size_t u8 ;
typedef  int u32 ;
struct tga_par {int htimings; int vtimings; int sync_on_green; int xres; int yres; int pll_freq; int bits_per_pixel; size_t tga_type; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int line_length; } ;
struct TYPE_3__ {int xres; int yres; int right_margin; int lower_margin; int hsync_len; int vsync_len; int left_margin; int upper_margin; int sync; int pixclock; int bits_per_pixel; } ;
struct fb_info {TYPE_2__ fix; TYPE_1__ var; scalar_t__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT459_CMD_REG_0 ; 
 int /*<<< orphan*/  BT459_CMD_REG_1 ; 
 int /*<<< orphan*/  BT459_CMD_REG_2 ; 
 int /*<<< orphan*/  BT459_CUR_CMD_REG ; 
 int /*<<< orphan*/  BT459_LOAD_ADDR (struct tga_par*,int) ; 
 int BT459_PALETTE ; 
 int /*<<< orphan*/  BT459_REG_ACC ; 
 int /*<<< orphan*/  BT459_WRITE (struct tga_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BT463_BLINK_MASK_0 ; 
 int /*<<< orphan*/  BT463_BLINK_MASK_1 ; 
 int /*<<< orphan*/  BT463_BLINK_MASK_2 ; 
 int /*<<< orphan*/  BT463_BLINK_MASK_3 ; 
 int /*<<< orphan*/  BT463_CMD_REG_0 ; 
 int /*<<< orphan*/  BT463_CMD_REG_1 ; 
 int /*<<< orphan*/  BT463_CMD_REG_2 ; 
 int /*<<< orphan*/  BT463_LOAD_ADDR (struct tga_par*,int) ; 
 int BT463_PALETTE ; 
 int /*<<< orphan*/  BT463_READ_MASK_0 ; 
 int /*<<< orphan*/  BT463_READ_MASK_1 ; 
 int /*<<< orphan*/  BT463_READ_MASK_2 ; 
 int /*<<< orphan*/  BT463_READ_MASK_3 ; 
 int BT463_REG_ACC ; 
 int BT463_WINDOW_TYPE_BASE ; 
 int /*<<< orphan*/  BT463_WRITE (struct tga_par*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BT485_ADDR_PAL_WRITE ; 
 int /*<<< orphan*/  BT485_CMD_0 ; 
 int /*<<< orphan*/  BT485_CMD_1 ; 
 int /*<<< orphan*/  BT485_CMD_2 ; 
 int /*<<< orphan*/  BT485_CMD_3 ; 
 int BT485_DATA_PAL ; 
 int /*<<< orphan*/  BT485_PIXEL_MASK ; 
 int /*<<< orphan*/  BT485_WRITE (struct tga_par*,int,int /*<<< orphan*/ ) ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_ON_GREEN ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int /*<<< orphan*/  TGA_BASE_ADDR_REG ; 
 int TGA_BUS_TC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TGA_CMD_STAT_REG ; 
 int /*<<< orphan*/  TGA_DEEP_REG ; 
 int TGA_HORIZ_ACT_LSB ; 
 int TGA_HORIZ_ACT_MSB ; 
 int TGA_HORIZ_BP ; 
 int TGA_HORIZ_FP ; 
 int TGA_HORIZ_POLARITY ; 
 int /*<<< orphan*/  TGA_HORIZ_REG ; 
 int TGA_HORIZ_SYNC ; 
 int /*<<< orphan*/  TGA_INTR_STAT_REG ; 
 int /*<<< orphan*/  TGA_MODE_REG ; 
 int /*<<< orphan*/  TGA_PIXELMASK_REG ; 
 int /*<<< orphan*/  TGA_PLANEMASK_REG ; 
 int /*<<< orphan*/  TGA_RAMDAC_REG ; 
 int /*<<< orphan*/  TGA_RAMDAC_SETUP_REG ; 
 int /*<<< orphan*/  TGA_RASTEROP_REG ; 
 int TGA_READ_REG (struct tga_par*,int /*<<< orphan*/ ) ; 
 size_t TGA_TYPE_8PLANE ; 
 int TGA_VALID_BLANK ; 
 int /*<<< orphan*/  TGA_VALID_REG ; 
 int TGA_VALID_VIDEO ; 
 int TGA_VERT_ACTIVE ; 
 int TGA_VERT_BP ; 
 int TGA_VERT_FP ; 
 int TGA_VERT_POLARITY ; 
 int /*<<< orphan*/  TGA_VERT_REG ; 
 int TGA_VERT_SYNC ; 
 int /*<<< orphan*/  TGA_WRITE_REG (struct tga_par*,unsigned int const,int /*<<< orphan*/ ) ; 
 int dev_is_pci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  tgafb_set_pll (struct tga_par*,int) ; 

__attribute__((used)) static int
tgafb_set_par(struct fb_info *info)
{
	static unsigned int const deep_presets[4] = {
		0x00004000,
		0x0000440d,
		0xffffffff,
		0x0000441d
	};
	static unsigned int const rasterop_presets[4] = {
		0x00000003,
		0x00000303,
		0xffffffff,
		0x00000303
	};
	static unsigned int const mode_presets[4] = {
		0x00000000,
		0x00000300,
		0xffffffff,
		0x00000300
	};
	static unsigned int const base_addr_presets[4] = {
		0x00000000,
		0x00000001,
		0xffffffff,
		0x00000001
	};

	struct tga_par *par = (struct tga_par *) info->par;
	int tga_bus_pci = dev_is_pci(par->dev);
	int tga_bus_tc = TGA_BUS_TC(par->dev);
	u32 htimings, vtimings, pll_freq;
	u8 tga_type;
	int i;

	/* Encode video timings.  */
	htimings = (((info->var.xres/4) & TGA_HORIZ_ACT_LSB)
		    | (((info->var.xres/4) & 0x600 << 19) & TGA_HORIZ_ACT_MSB));
	vtimings = (info->var.yres & TGA_VERT_ACTIVE);
	htimings |= ((info->var.right_margin/4) << 9) & TGA_HORIZ_FP;
	vtimings |= (info->var.lower_margin << 11) & TGA_VERT_FP;
	htimings |= ((info->var.hsync_len/4) << 14) & TGA_HORIZ_SYNC;
	vtimings |= (info->var.vsync_len << 16) & TGA_VERT_SYNC;
	htimings |= ((info->var.left_margin/4) << 21) & TGA_HORIZ_BP;
	vtimings |= (info->var.upper_margin << 22) & TGA_VERT_BP;

	if (info->var.sync & FB_SYNC_HOR_HIGH_ACT)
		htimings |= TGA_HORIZ_POLARITY;
	if (info->var.sync & FB_SYNC_VERT_HIGH_ACT)
		vtimings |= TGA_VERT_POLARITY;

	par->htimings = htimings;
	par->vtimings = vtimings;

	par->sync_on_green = !!(info->var.sync & FB_SYNC_ON_GREEN);

	/* Store other useful values in par.  */
	par->xres = info->var.xres;
	par->yres = info->var.yres;
	par->pll_freq = pll_freq = 1000000000 / info->var.pixclock;
	par->bits_per_pixel = info->var.bits_per_pixel;
	info->fix.line_length = par->xres * (par->bits_per_pixel >> 3);

	tga_type = par->tga_type;

	/* First, disable video.  */
	TGA_WRITE_REG(par, TGA_VALID_VIDEO | TGA_VALID_BLANK, TGA_VALID_REG);

	/* Write the DEEP register.  */
	while (TGA_READ_REG(par, TGA_CMD_STAT_REG) & 1) /* wait for not busy */
		continue;
	mb();
	TGA_WRITE_REG(par, deep_presets[tga_type] |
			   (par->sync_on_green ? 0x0 : 0x00010000),
		      TGA_DEEP_REG);
	while (TGA_READ_REG(par, TGA_CMD_STAT_REG) & 1) /* wait for not busy */
		continue;
	mb();

	/* Write some more registers.  */
	TGA_WRITE_REG(par, rasterop_presets[tga_type], TGA_RASTEROP_REG);
	TGA_WRITE_REG(par, mode_presets[tga_type], TGA_MODE_REG);
	TGA_WRITE_REG(par, base_addr_presets[tga_type], TGA_BASE_ADDR_REG);

	/* Calculate & write the PLL.  */
	tgafb_set_pll(par, pll_freq);

	/* Write some more registers.  */
	TGA_WRITE_REG(par, 0xffffffff, TGA_PLANEMASK_REG);
	TGA_WRITE_REG(par, 0xffffffff, TGA_PIXELMASK_REG);

	/* Init video timing regs.  */
	TGA_WRITE_REG(par, htimings, TGA_HORIZ_REG);
	TGA_WRITE_REG(par, vtimings, TGA_VERT_REG);

	/* Initialise RAMDAC. */
	if (tga_type == TGA_TYPE_8PLANE && tga_bus_pci) {

		/* Init BT485 RAMDAC registers.  */
		BT485_WRITE(par, 0xa2 | (par->sync_on_green ? 0x8 : 0x0),
			    BT485_CMD_0);
		BT485_WRITE(par, 0x01, BT485_ADDR_PAL_WRITE);
		BT485_WRITE(par, 0x14, BT485_CMD_3); /* cursor 64x64 */
		BT485_WRITE(par, 0x40, BT485_CMD_1);
		BT485_WRITE(par, 0x20, BT485_CMD_2); /* cursor off, for now */
		BT485_WRITE(par, 0xff, BT485_PIXEL_MASK);

		/* Fill palette registers.  */
		BT485_WRITE(par, 0x00, BT485_ADDR_PAL_WRITE);
		TGA_WRITE_REG(par, BT485_DATA_PAL, TGA_RAMDAC_SETUP_REG);

		for (i = 0; i < 256 * 3; i += 4) {
			TGA_WRITE_REG(par, 0x55 | (BT485_DATA_PAL << 8),
				      TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00 | (BT485_DATA_PAL << 8),
				      TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00 | (BT485_DATA_PAL << 8),
				      TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00 | (BT485_DATA_PAL << 8),
				      TGA_RAMDAC_REG);
		}

	} else if (tga_type == TGA_TYPE_8PLANE && tga_bus_tc) {

		/* Init BT459 RAMDAC registers.  */
		BT459_WRITE(par, BT459_REG_ACC, BT459_CMD_REG_0, 0x40);
		BT459_WRITE(par, BT459_REG_ACC, BT459_CMD_REG_1, 0x00);
		BT459_WRITE(par, BT459_REG_ACC, BT459_CMD_REG_2,
			    (par->sync_on_green ? 0xc0 : 0x40));

		BT459_WRITE(par, BT459_REG_ACC, BT459_CUR_CMD_REG, 0x00);

		/* Fill the palette.  */
		BT459_LOAD_ADDR(par, 0x0000);
		TGA_WRITE_REG(par, BT459_PALETTE << 2, TGA_RAMDAC_SETUP_REG);

		for (i = 0; i < 256 * 3; i += 4) {
			TGA_WRITE_REG(par, 0x55, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
		}

	} else { /* 24-plane or 24plusZ */

		/* Init BT463 RAMDAC registers.  */
		BT463_WRITE(par, BT463_REG_ACC, BT463_CMD_REG_0, 0x40);
		BT463_WRITE(par, BT463_REG_ACC, BT463_CMD_REG_1, 0x08);
		BT463_WRITE(par, BT463_REG_ACC, BT463_CMD_REG_2,
			    (par->sync_on_green ? 0xc0 : 0x40));

		BT463_WRITE(par, BT463_REG_ACC, BT463_READ_MASK_0, 0xff);
		BT463_WRITE(par, BT463_REG_ACC, BT463_READ_MASK_1, 0xff);
		BT463_WRITE(par, BT463_REG_ACC, BT463_READ_MASK_2, 0xff);
		BT463_WRITE(par, BT463_REG_ACC, BT463_READ_MASK_3, 0x0f);

		BT463_WRITE(par, BT463_REG_ACC, BT463_BLINK_MASK_0, 0x00);
		BT463_WRITE(par, BT463_REG_ACC, BT463_BLINK_MASK_1, 0x00);
		BT463_WRITE(par, BT463_REG_ACC, BT463_BLINK_MASK_2, 0x00);
		BT463_WRITE(par, BT463_REG_ACC, BT463_BLINK_MASK_3, 0x00);

		/* Fill the palette.  */
		BT463_LOAD_ADDR(par, 0x0000);
		TGA_WRITE_REG(par, BT463_PALETTE << 2, TGA_RAMDAC_SETUP_REG);

#ifdef CONFIG_HW_CONSOLE
		for (i = 0; i < 16; i++) {
			int j = color_table[i];

			TGA_WRITE_REG(par, default_red[j], TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, default_grn[j], TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, default_blu[j], TGA_RAMDAC_REG);
		}
		for (i = 0; i < 512 * 3; i += 4) {
#else
		for (i = 0; i < 528 * 3; i += 4) {
#endif
			TGA_WRITE_REG(par, 0x55, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
		}

		/* Fill window type table after start of vertical retrace.  */
		while (!(TGA_READ_REG(par, TGA_INTR_STAT_REG) & 0x01))
			continue;
		TGA_WRITE_REG(par, 0x01, TGA_INTR_STAT_REG);
		mb();
		while (!(TGA_READ_REG(par, TGA_INTR_STAT_REG) & 0x01))
			continue;
		TGA_WRITE_REG(par, 0x01, TGA_INTR_STAT_REG);

		BT463_LOAD_ADDR(par, BT463_WINDOW_TYPE_BASE);
		TGA_WRITE_REG(par, BT463_REG_ACC << 2, TGA_RAMDAC_SETUP_REG);

		for (i = 0; i < 16; i++) {
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x01, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
		}

	}

	/* Finally, enable video scan (and pray for the monitor... :-) */
	TGA_WRITE_REG(par, TGA_VALID_VIDEO, TGA_VALID_REG);

	return 0;
}