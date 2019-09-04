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
typedef  int /*<<< orphan*/  var ;
typedef  int u32 ;
struct fb_var_screeninfo {scalar_t__ yres; scalar_t__ yres_virtual; int bits_per_pixel; int xres_virtual; int /*<<< orphan*/  sync; int /*<<< orphan*/  accel_flags; } ;
struct TYPE_5__ {int smem_len; int mmio_len; int mmio_start; int /*<<< orphan*/  id; int /*<<< orphan*/  accel; } ;
struct fb_info {int flags; TYPE_1__ fix; int /*<<< orphan*/  node; int /*<<< orphan*/  cmap; struct fb_var_screeninfo var; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/ * fbops; scalar_t__ par; } ;
struct TYPE_7__ {int pll_max; int mclk; int xclk; } ;
struct TYPE_6__ {int /*<<< orphan*/  wait; } ;
struct atyfb_par {int pll_per; int mclk_per; int xclk_per; unsigned long long ref_clk_per; int mem_cntl; scalar_t__ bus_type; int /*<<< orphan*/  wc_cookie; int /*<<< orphan*/  saved_pll; TYPE_4__* pll_ops; int /*<<< orphan*/  saved_crtc; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/  res_size; int /*<<< orphan*/  res_start; scalar_t__ aux_start; int /*<<< orphan*/  pll; TYPE_3__ pll_limits; int /*<<< orphan*/  int_lock; TYPE_2__ vblank; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_pll ) (struct fb_info*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* resume_pll ) (struct fb_info*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* init_pll ) (struct fb_info*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_pll ) (struct fb_info*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int BUS_APER_REG_DIS ; 
 int /*<<< orphan*/  BUS_CNTL ; 
 int /*<<< orphan*/  CNFG_STAT1 ; 
 int /*<<< orphan*/  CT ; 
 int FBINFO_DEFAULT ; 
 int FBINFO_HWACCEL_COPYAREA ; 
 int FBINFO_HWACCEL_FILLRECT ; 
 int FBINFO_HWACCEL_IMAGEBLIT ; 
 int FBINFO_HWACCEL_YPAN ; 
 int FBINFO_READS_FAST ; 
 int /*<<< orphan*/  FB_ACCELF_TEXT ; 
 int /*<<< orphan*/  FB_ACCEL_ATI_MACH64CT ; 
 int /*<<< orphan*/  FB_ACCEL_ATI_MACH64GT ; 
 int /*<<< orphan*/  FB_ACCEL_ATI_MACH64GX ; 
 int /*<<< orphan*/  FB_ACCEL_ATI_MACH64VT ; 
 int /*<<< orphan*/  FB_SYNC_COMP_HIGH_ACT ; 
 int /*<<< orphan*/  GTB_DSP ; 
 int /*<<< orphan*/  GX ; 
 scalar_t__ ISA ; 
 int M64_HAS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_VRAM_SIZE ; 
 int /*<<< orphan*/  MEM_CNTL ; 
#define  MEM_SIZE_1M 137 
#define  MEM_SIZE_2M 136 
#define  MEM_SIZE_2M_GTB 135 
#define  MEM_SIZE_4M 134 
#define  MEM_SIZE_4M_GTB 133 
#define  MEM_SIZE_512K 132 
#define  MEM_SIZE_6M 131 
#define  MEM_SIZE_6M_GTB 130 
#define  MEM_SIZE_8M 129 
#define  MEM_SIZE_8M_GTB 128 
 int MEM_SIZE_ALIAS ; 
 int /*<<< orphan*/  MOBIL_BUS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PRINTKE (char*) ; 
 int /*<<< orphan*/  PRINTKI (char*,int,char,char const*,...) ; 
 int /*<<< orphan*/  VT ; 
 int /*<<< orphan*/  arch_phys_wc_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aty_calc_mem_refresh (struct atyfb_par*,int) ; 
 int /*<<< orphan*/  aty_fudge_framebuffer_len (struct fb_info*) ; 
 int /*<<< orphan*/  aty_get_crtc (struct atyfb_par*,int /*<<< orphan*/ *) ; 
 int aty_ld_le32 (int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_set_crtc (struct atyfb_par*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int,struct atyfb_par*) ; 
 int atyfb_check_var (struct fb_var_screeninfo*,struct fb_info*) ; 
 int /*<<< orphan*/  atyfb_ops ; 
 scalar_t__ backlight ; 
 int comp_sync ; 
 struct fb_var_screeninfo default_var ; 
 int /*<<< orphan*/  defmode ; 
 int fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 scalar_t__ fb_find_mode (struct fb_var_screeninfo*,struct fb_info*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct fb_info* fb_list ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int mclk ; 
 int /*<<< orphan*/  memset (struct fb_var_screeninfo*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mode ; 
 scalar_t__ noaccel ; 
 int /*<<< orphan*/  nomtrr ; 
 int pll ; 
 int register_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fb_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct fb_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct fb_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct fb_info*,int /*<<< orphan*/ *) ; 
 int vram ; 
 int xclk ; 

__attribute__((used)) static int aty_init(struct fb_info *info)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	const char *ramname = NULL, *xtal;
	int gtb_memsize, has_var = 0;
	struct fb_var_screeninfo var;
	int ret;

	init_waitqueue_head(&par->vblank.wait);
	spin_lock_init(&par->int_lock);

#ifdef CONFIG_FB_ATY_GX
	if (!M64_HAS(INTEGRATED)) {
		u32 stat0;
		u8 dac_type, dac_subtype, clk_type;
		stat0 = aty_ld_le32(CNFG_STAT0, par);
		par->bus_type = (stat0 >> 0) & 0x07;
		par->ram_type = (stat0 >> 3) & 0x07;
		ramname = aty_gx_ram[par->ram_type];
		/* FIXME: clockchip/RAMDAC probing? */
		dac_type = (aty_ld_le32(DAC_CNTL, par) >> 16) & 0x07;
#ifdef CONFIG_ATARI
		clk_type = CLK_ATI18818_1;
		dac_type = (stat0 >> 9) & 0x07;
		if (dac_type == 0x07)
			dac_subtype = DAC_ATT20C408;
		else
			dac_subtype = (aty_ld_8(SCRATCH_REG1 + 1, par) & 0xF0) | dac_type;
#else
		dac_type = DAC_IBMRGB514;
		dac_subtype = DAC_IBMRGB514;
		clk_type = CLK_IBMRGB514;
#endif
		switch (dac_subtype) {
		case DAC_IBMRGB514:
			par->dac_ops = &aty_dac_ibm514;
			break;
#ifdef CONFIG_ATARI
		case DAC_ATI68860_B:
		case DAC_ATI68860_C:
			par->dac_ops = &aty_dac_ati68860b;
			break;
		case DAC_ATT20C408:
		case DAC_ATT21C498:
			par->dac_ops = &aty_dac_att21c498;
			break;
#endif
		default:
			PRINTKI("aty_init: DAC type not implemented yet!\n");
			par->dac_ops = &aty_dac_unsupported;
			break;
		}
		switch (clk_type) {
#ifdef CONFIG_ATARI
		case CLK_ATI18818_1:
			par->pll_ops = &aty_pll_ati18818_1;
			break;
#else
		case CLK_IBMRGB514:
			par->pll_ops = &aty_pll_ibm514;
			break;
#endif
#if 0 /* dead code */
		case CLK_STG1703:
			par->pll_ops = &aty_pll_stg1703;
			break;
		case CLK_CH8398:
			par->pll_ops = &aty_pll_ch8398;
			break;
		case CLK_ATT20C408:
			par->pll_ops = &aty_pll_att20c408;
			break;
#endif
		default:
			PRINTKI("aty_init: CLK type not implemented yet!");
			par->pll_ops = &aty_pll_unsupported;
			break;
		}
	}
#endif /* CONFIG_FB_ATY_GX */
#ifdef CONFIG_FB_ATY_CT
	if (M64_HAS(INTEGRATED)) {
		par->dac_ops = &aty_dac_ct;
		par->pll_ops = &aty_pll_ct;
		par->bus_type = PCI;
		par->ram_type = (aty_ld_le32(CNFG_STAT0, par) & 0x07);
		if (M64_HAS(XL_MEM))
			ramname = aty_xl_ram[par->ram_type];
		else
			ramname = aty_ct_ram[par->ram_type];
		/* for many chips, the mclk is 67 MHz for SDRAM, 63 MHz otherwise */
		if (par->pll_limits.mclk == 67 && par->ram_type < SDRAM)
			par->pll_limits.mclk = 63;
		/* Mobility + 32bit memory interface need halved XCLK. */
		if (M64_HAS(MOBIL_BUS) && par->ram_type == SDRAM32)
			par->pll_limits.xclk = (par->pll_limits.xclk + 1) >> 1;
	}
#endif
#ifdef CONFIG_PPC_PMAC
	/*
	 * The Apple iBook1 uses non-standard memory frequencies.
	 * We detect it and set the frequency manually.
	 */
	if (of_machine_is_compatible("PowerBook2,1")) {
		par->pll_limits.mclk = 70;
		par->pll_limits.xclk = 53;
	}
#endif

	/* Allow command line to override clocks. */
	if (pll)
		par->pll_limits.pll_max = pll;
	if (mclk)
		par->pll_limits.mclk = mclk;
	if (xclk)
		par->pll_limits.xclk = xclk;

	aty_calc_mem_refresh(par, par->pll_limits.xclk);
	par->pll_per = 1000000/par->pll_limits.pll_max;
	par->mclk_per = 1000000/par->pll_limits.mclk;
	par->xclk_per = 1000000/par->pll_limits.xclk;

	par->ref_clk_per = 1000000000000ULL / 14318180;
	xtal = "14.31818";

#ifdef CONFIG_FB_ATY_CT
	if (M64_HAS(GTB_DSP)) {
		u8 pll_ref_div = aty_ld_pll_ct(PLL_REF_DIV, par);

		if (pll_ref_div) {
			int diff1, diff2;
			diff1 = 510 * 14 / pll_ref_div - par->pll_limits.pll_max;
			diff2 = 510 * 29 / pll_ref_div - par->pll_limits.pll_max;
			if (diff1 < 0)
				diff1 = -diff1;
			if (diff2 < 0)
				diff2 = -diff2;
			if (diff2 < diff1) {
				par->ref_clk_per = 1000000000000ULL / 29498928;
				xtal = "29.498928";
			}
		}
	}
#endif /* CONFIG_FB_ATY_CT */

	/* save previous video mode */
	aty_get_crtc(par, &par->saved_crtc);
	if (par->pll_ops->get_pll)
		par->pll_ops->get_pll(info, &par->saved_pll);

	par->mem_cntl = aty_ld_le32(MEM_CNTL, par);
	gtb_memsize = M64_HAS(GTB_DSP);
	if (gtb_memsize)
		/* 0xF used instead of MEM_SIZE_ALIAS */
		switch (par->mem_cntl & 0xF) {
		case MEM_SIZE_512K:
			info->fix.smem_len = 0x80000;
			break;
		case MEM_SIZE_1M:
			info->fix.smem_len = 0x100000;
			break;
		case MEM_SIZE_2M_GTB:
			info->fix.smem_len = 0x200000;
			break;
		case MEM_SIZE_4M_GTB:
			info->fix.smem_len = 0x400000;
			break;
		case MEM_SIZE_6M_GTB:
			info->fix.smem_len = 0x600000;
			break;
		case MEM_SIZE_8M_GTB:
			info->fix.smem_len = 0x800000;
			break;
		default:
			info->fix.smem_len = 0x80000;
	} else
		switch (par->mem_cntl & MEM_SIZE_ALIAS) {
		case MEM_SIZE_512K:
			info->fix.smem_len = 0x80000;
			break;
		case MEM_SIZE_1M:
			info->fix.smem_len = 0x100000;
			break;
		case MEM_SIZE_2M:
			info->fix.smem_len = 0x200000;
			break;
		case MEM_SIZE_4M:
			info->fix.smem_len = 0x400000;
			break;
		case MEM_SIZE_6M:
			info->fix.smem_len = 0x600000;
			break;
		case MEM_SIZE_8M:
			info->fix.smem_len = 0x800000;
			break;
		default:
			info->fix.smem_len = 0x80000;
		}

	if (M64_HAS(MAGIC_VRAM_SIZE)) {
		if (aty_ld_le32(CNFG_STAT1, par) & 0x40000000)
			info->fix.smem_len += 0x400000;
	}

	if (vram) {
		info->fix.smem_len = vram * 1024;
		par->mem_cntl &= ~(gtb_memsize ? 0xF : MEM_SIZE_ALIAS);
		if (info->fix.smem_len <= 0x80000)
			par->mem_cntl |= MEM_SIZE_512K;
		else if (info->fix.smem_len <= 0x100000)
			par->mem_cntl |= MEM_SIZE_1M;
		else if (info->fix.smem_len <= 0x200000)
			par->mem_cntl |= gtb_memsize ? MEM_SIZE_2M_GTB : MEM_SIZE_2M;
		else if (info->fix.smem_len <= 0x400000)
			par->mem_cntl |= gtb_memsize ? MEM_SIZE_4M_GTB : MEM_SIZE_4M;
		else if (info->fix.smem_len <= 0x600000)
			par->mem_cntl |= gtb_memsize ? MEM_SIZE_6M_GTB : MEM_SIZE_6M;
		else
			par->mem_cntl |= gtb_memsize ? MEM_SIZE_8M_GTB : MEM_SIZE_8M;
		aty_st_le32(MEM_CNTL, par->mem_cntl, par);
	}

	/*
	 * Reg Block 0 (CT-compatible block) is at mmio_start
	 * Reg Block 1 (multimedia extensions) is at mmio_start - 0x400
	 */
	if (M64_HAS(GX)) {
		info->fix.mmio_len = 0x400;
		info->fix.accel = FB_ACCEL_ATI_MACH64GX;
	} else if (M64_HAS(CT)) {
		info->fix.mmio_len = 0x400;
		info->fix.accel = FB_ACCEL_ATI_MACH64CT;
	} else if (M64_HAS(VT)) {
		info->fix.mmio_start -= 0x400;
		info->fix.mmio_len = 0x800;
		info->fix.accel = FB_ACCEL_ATI_MACH64VT;
	} else {/* GT */
		info->fix.mmio_start -= 0x400;
		info->fix.mmio_len = 0x800;
		info->fix.accel = FB_ACCEL_ATI_MACH64GT;
	}

	PRINTKI("%d%c %s, %s MHz XTAL, %d MHz PLL, %d Mhz MCLK, %d MHz XCLK\n",
		info->fix.smem_len == 0x80000 ? 512 : (info->fix.smem_len>>20),
		info->fix.smem_len == 0x80000 ? 'K' : 'M', ramname, xtal,
		par->pll_limits.pll_max, par->pll_limits.mclk,
		par->pll_limits.xclk);

#if defined(DEBUG) && defined(CONFIG_FB_ATY_CT)
	if (M64_HAS(INTEGRATED)) {
		int i;
		printk("debug atyfb: BUS_CNTL DAC_CNTL MEM_CNTL "
		       "EXT_MEM_CNTL CRTC_GEN_CNTL DSP_CONFIG "
		       "DSP_ON_OFF CLOCK_CNTL\n"
		       "debug atyfb: %08x %08x %08x "
		       "%08x     %08x      %08x   "
		       "%08x   %08x\n"
		       "debug atyfb: PLL",
		       aty_ld_le32(BUS_CNTL, par),
		       aty_ld_le32(DAC_CNTL, par),
		       aty_ld_le32(MEM_CNTL, par),
		       aty_ld_le32(EXT_MEM_CNTL, par),
		       aty_ld_le32(CRTC_GEN_CNTL, par),
		       aty_ld_le32(DSP_CONFIG, par),
		       aty_ld_le32(DSP_ON_OFF, par),
		       aty_ld_le32(CLOCK_CNTL, par));
		for (i = 0; i < 40; i++)
			printk(" %02x", aty_ld_pll_ct(i, par));
		printk("\n");
	}
#endif
	if (par->pll_ops->init_pll)
		par->pll_ops->init_pll(info, &par->pll);
	if (par->pll_ops->resume_pll)
		par->pll_ops->resume_pll(info, &par->pll);

	aty_fudge_framebuffer_len(info);

	/*
	 * Disable register access through the linear aperture
	 * if the auxiliary aperture is used so we can access
	 * the full 8 MB of video RAM on 8 MB boards.
	 */
	if (par->aux_start)
		aty_st_le32(BUS_CNTL, aty_ld_le32(BUS_CNTL, par) |
			    BUS_APER_REG_DIS, par);

	if (!nomtrr)
		/*
		 * Only the ioremap_wc()'d area will get WC here
		 * since ioremap_uc() was used on the entire PCI BAR.
		 */
		par->wc_cookie = arch_phys_wc_add(par->res_start,
						  par->res_size);

	info->fbops = &atyfb_ops;
	info->pseudo_palette = par->pseudo_palette;
	info->flags = FBINFO_DEFAULT           |
		      FBINFO_HWACCEL_IMAGEBLIT |
		      FBINFO_HWACCEL_FILLRECT  |
		      FBINFO_HWACCEL_COPYAREA  |
		      FBINFO_HWACCEL_YPAN      |
		      FBINFO_READS_FAST;

#ifdef CONFIG_PMAC_BACKLIGHT
	if (M64_HAS(G3_PB_1_1) && of_machine_is_compatible("PowerBook1,1")) {
		/*
		 * these bits let the 101 powerbook
		 * wake up from sleep -- paulus
		 */
		aty_st_lcd(POWER_MANAGEMENT, aty_ld_lcd(POWER_MANAGEMENT, par) |
			   USE_F32KHZ | TRISTATE_MEM_EN, par);
	} else
#endif
	if (M64_HAS(MOBIL_BUS) && backlight) {
#ifdef CONFIG_FB_ATY_BACKLIGHT
		aty_bl_init(par);
#endif
	}

	memset(&var, 0, sizeof(var));
#ifdef CONFIG_PPC
	if (machine_is(powermac)) {
		/*
		 * FIXME: The NVRAM stuff should be put in a Mac-specific file,
		 *        as it applies to all Mac video cards
		 */
		if (mode) {
			if (mac_find_mode(&var, info, mode, 8))
				has_var = 1;
		} else {
			if (default_vmode == VMODE_CHOOSE) {
				int sense;
				if (M64_HAS(G3_PB_1024x768))
					/* G3 PowerBook with 1024x768 LCD */
					default_vmode = VMODE_1024_768_60;
				else if (of_machine_is_compatible("iMac"))
					default_vmode = VMODE_1024_768_75;
				else if (of_machine_is_compatible("PowerBook2,1"))
					/* iBook with 800x600 LCD */
					default_vmode = VMODE_800_600_60;
				else
					default_vmode = VMODE_640_480_67;
				sense = read_aty_sense(par);
				PRINTKI("monitor sense=%x, mode %d\n",
					sense,  mac_map_monitor_sense(sense));
			}
			if (default_vmode <= 0 || default_vmode > VMODE_MAX)
				default_vmode = VMODE_640_480_60;
			if (default_cmode < CMODE_8 || default_cmode > CMODE_32)
				default_cmode = CMODE_8;
			if (!mac_vmode_to_var(default_vmode, default_cmode,
					      &var))
				has_var = 1;
		}
	}

#endif /* !CONFIG_PPC */

#if defined(__i386__) && defined(CONFIG_FB_ATY_GENERIC_LCD)
	if (!atyfb_get_timings_from_lcd(par, &var))
		has_var = 1;
#endif

	if (mode && fb_find_mode(&var, info, mode, NULL, 0, &defmode, 8))
		has_var = 1;

	if (!has_var)
		var = default_var;

	if (noaccel)
		var.accel_flags &= ~FB_ACCELF_TEXT;
	else
		var.accel_flags |= FB_ACCELF_TEXT;

	if (comp_sync != -1) {
		if (!comp_sync)
			var.sync &= ~FB_SYNC_COMP_HIGH_ACT;
		else
			var.sync |= FB_SYNC_COMP_HIGH_ACT;
	}

	if (var.yres == var.yres_virtual) {
		u32 videoram = (info->fix.smem_len - (PAGE_SIZE << 2));
		var.yres_virtual = ((videoram * 8) / var.bits_per_pixel) / var.xres_virtual;
		if (var.yres_virtual < var.yres)
			var.yres_virtual = var.yres;
	}

	ret = atyfb_check_var(&var, info);
	if (ret) {
		PRINTKE("can't set default video mode\n");
		goto aty_init_exit;
	}

#ifdef CONFIG_FB_ATY_CT
	if (!noaccel && M64_HAS(INTEGRATED))
		aty_init_cursor(info);
#endif /* CONFIG_FB_ATY_CT */
	info->var = var;

	ret = fb_alloc_cmap(&info->cmap, 256, 0);
	if (ret < 0)
		goto aty_init_exit;

	ret = register_framebuffer(info);
	if (ret < 0) {
		fb_dealloc_cmap(&info->cmap);
		goto aty_init_exit;
	}

	fb_list = info;

	PRINTKI("fb%d: %s frame buffer device on %s\n",
		info->node, info->fix.id, par->bus_type == ISA ? "ISA" : "PCI");
	return 0;

aty_init_exit:
	/* restore video mode */
	aty_set_crtc(par, &par->saved_crtc);
	par->pll_ops->set_pll(info, &par->saved_pll);
	arch_phys_wc_del(par->wc_cookie);

	return ret;
}