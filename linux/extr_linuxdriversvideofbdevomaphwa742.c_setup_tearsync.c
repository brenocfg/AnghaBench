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
typedef  int u8 ;
struct TYPE_5__ {unsigned long we_cycle_time; } ;
struct TYPE_8__ {unsigned long pix_tx_time; int line_upd_time; int vsync_only; TYPE_3__* extif; TYPE_2__* fbdev; TYPE_1__ reg_timings; } ;
struct TYPE_7__ {unsigned long (* get_max_tx_rate ) () ;int (* setup_tearsync ) (int,int,int,int,int,int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EDOM ; 
 int /*<<< orphan*/  HWA742_HS_W_REG ; 
 int /*<<< orphan*/  HWA742_H_DISP_REG ; 
 int /*<<< orphan*/  HWA742_H_NDP_REG ; 
 int /*<<< orphan*/  HWA742_NDP_CTRL ; 
 int /*<<< orphan*/  HWA742_VS_W_REG ; 
 int /*<<< orphan*/  HWA742_V_DISP_1_REG ; 
 int /*<<< orphan*/  HWA742_V_DISP_2_REG ; 
 int /*<<< orphan*/  HWA742_V_NDP_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 TYPE_4__ hwa742 ; 
 int hwa742_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwa742_write_reg (int /*<<< orphan*/ ,int) ; 
 unsigned long stub1 () ; 
 int stub2 (int,int,int,int,int,int) ; 

__attribute__((used)) static int setup_tearsync(unsigned long pix_clk, int extif_div)
{
	int hdisp, vdisp;
	int hndp, vndp;
	int hsw, vsw;
	int hs, vs;
	int hs_pol_inv, vs_pol_inv;
	int use_hsvs, use_ndp;
	u8  b;

	hsw = hwa742_read_reg(HWA742_HS_W_REG);
	vsw = hwa742_read_reg(HWA742_VS_W_REG);
	hs_pol_inv = !(hsw & 0x80);
	vs_pol_inv = !(vsw & 0x80);
	hsw = hsw & 0x7f;
	vsw = vsw & 0x3f;

	hdisp = (hwa742_read_reg(HWA742_H_DISP_REG) & 0x7f) * 8;
	vdisp = hwa742_read_reg(HWA742_V_DISP_1_REG) +
		((hwa742_read_reg(HWA742_V_DISP_2_REG) & 0x3) << 8);

	hndp = hwa742_read_reg(HWA742_H_NDP_REG) & 0x7f;
	vndp = hwa742_read_reg(HWA742_V_NDP_REG);

	/* time to transfer one pixel (16bpp) in ps */
	hwa742.pix_tx_time = hwa742.reg_timings.we_cycle_time;
	if (hwa742.extif->get_max_tx_rate != NULL) {
		/*
		 * The external interface might have a rate limitation,
		 * if so, we have to maximize our transfer rate.
		 */
		unsigned long min_tx_time;
		unsigned long max_tx_rate = hwa742.extif->get_max_tx_rate();

		dev_dbg(hwa742.fbdev->dev, "max_tx_rate %ld HZ\n",
			max_tx_rate);
		min_tx_time = 1000000000 / (max_tx_rate / 1000);  /* ps */
		if (hwa742.pix_tx_time < min_tx_time)
			hwa742.pix_tx_time = min_tx_time;
	}

	/* time to update one line in ps */
	hwa742.line_upd_time = (hdisp + hndp) * 1000000 / (pix_clk / 1000);
	hwa742.line_upd_time *= 1000;
	if (hdisp * hwa742.pix_tx_time > hwa742.line_upd_time)
		/*
		 * transfer speed too low, we might have to use both
		 * HS and VS
		 */
		use_hsvs = 1;
	else
		/* decent transfer speed, we'll always use only VS */
		use_hsvs = 0;

	if (use_hsvs && (hs_pol_inv || vs_pol_inv)) {
		/*
		 * HS or'ed with VS doesn't work, use the active high
		 * TE signal based on HNDP / VNDP
		 */
		use_ndp = 1;
		hs_pol_inv = 0;
		vs_pol_inv = 0;
		hs = hndp;
		vs = vndp;
	} else {
		/*
		 * Use HS or'ed with VS as a TE signal if both are needed
		 * or VNDP if only vsync is needed.
		 */
		use_ndp = 0;
		hs = hsw;
		vs = vsw;
		if (!use_hsvs) {
			hs_pol_inv = 0;
			vs_pol_inv = 0;
		}
	}

	hs = hs * 1000000 / (pix_clk / 1000);			/* ps */
	hs *= 1000;

	vs = vs * (hdisp + hndp) * 1000000 / (pix_clk / 1000);	/* ps */
	vs *= 1000;

	if (vs <= hs)
		return -EDOM;
	/* set VS to 120% of HS to minimize VS detection time */
	vs = hs * 12 / 10;
	/* minimize HS too */
	hs = 10000;

	b = hwa742_read_reg(HWA742_NDP_CTRL);
	b &= ~0x3;
	b |= use_hsvs ? 1 : 0;
	b |= (use_ndp && use_hsvs) ? 0 : 2;
	hwa742_write_reg(HWA742_NDP_CTRL, b);

	hwa742.vsync_only = !use_hsvs;

	dev_dbg(hwa742.fbdev->dev,
		"pix_clk %ld HZ pix_tx_time %ld ps line_upd_time %ld ps\n",
		pix_clk, hwa742.pix_tx_time, hwa742.line_upd_time);
	dev_dbg(hwa742.fbdev->dev,
		"hs %d ps vs %d ps mode %d vsync_only %d\n",
		hs, vs, (b & 0x3), !use_hsvs);

	return hwa742.extif->setup_tearsync(1, hs, vs,
					    hs_pol_inv, vs_pol_inv, extif_div);
}