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
typedef  int u16 ;
struct omap_video_timings {int dummy; } ;
typedef  enum omap_color_mode { ____Placeholder_omap_color_mode } omap_color_mode ;
struct TYPE_4__ {TYPE_1__* feat; } ;
struct TYPE_3__ {unsigned long (* calc_core_clk ) (unsigned long,int,int,int,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FEAT_PARAM_LINEWIDTH ; 
 unsigned long calc_core_clk_five_taps (unsigned long,struct omap_video_timings const*,int,int,int,int,int) ; 
 int check_horiz_timing_omap3 (unsigned long,unsigned long,struct omap_video_timings const*,int,int,int,int,int,int) ; 
 TYPE_2__ dispc ; 
 unsigned long dispc_core_clk_rate () ; 
 int dss_feat_get_param_max (int /*<<< orphan*/ ) ; 
 unsigned long stub1 (unsigned long,int,int,int,int,int) ; 

__attribute__((used)) static int dispc_ovl_calc_scaling_34xx(unsigned long pclk, unsigned long lclk,
		const struct omap_video_timings *mgr_timings,
		u16 width, u16 height, u16 out_width, u16 out_height,
		enum omap_color_mode color_mode, bool *five_taps,
		int *x_predecim, int *y_predecim, int *decim_x, int *decim_y,
		u16 pos_x, unsigned long *core_clk, bool mem_to_mem)
{
	int error;
	u16 in_width, in_height;
	const int maxsinglelinewidth =
			dss_feat_get_param_max(FEAT_PARAM_LINEWIDTH);

	do {
		in_height = height / *decim_y;
		in_width = width / *decim_x;
		*five_taps = in_height > out_height;

		if (in_width > maxsinglelinewidth)
			if (in_height > out_height &&
						in_height < out_height * 2)
				*five_taps = false;
again:
		if (*five_taps)
			*core_clk = calc_core_clk_five_taps(pclk, mgr_timings,
						in_width, in_height, out_width,
						out_height, color_mode);
		else
			*core_clk = dispc.feat->calc_core_clk(pclk, in_width,
					in_height, out_width, out_height,
					mem_to_mem);

		error = check_horiz_timing_omap3(pclk, lclk, mgr_timings,
				pos_x, in_width, in_height, out_width,
				out_height, *five_taps);
		if (error && *five_taps) {
			*five_taps = false;
			goto again;
		}

		error = (error || in_width > maxsinglelinewidth * 2 ||
			(in_width > maxsinglelinewidth && *five_taps) ||
			!*core_clk || *core_clk > dispc_core_clk_rate());

		if (!error) {
			/* verify that we're inside the limits of scaler */
			if (in_width / 4 > out_width)
					error = 1;

			if (*five_taps) {
				if (in_height / 4 > out_height)
					error = 1;
			} else {
				if (in_height / 2 > out_height)
					error = 1;
			}
		}

		if (error)
			++*decim_y;
	} while (*decim_x <= *x_predecim && *decim_y <= *y_predecim && error);

	if (error) {
		DSSERR("failed to find scaling settings\n");
		return -EINVAL;
	}

	if (check_horiz_timing_omap3(pclk, lclk, mgr_timings, pos_x, in_width,
				in_height, out_width, out_height, *five_taps)) {
			DSSERR("horizontal timing too tight\n");
			return -EINVAL;
	}

	if (in_width > (maxsinglelinewidth * 2)) {
		DSSERR("Cannot setup scaling");
		DSSERR("width exceeds maximum width possible");
		return -EINVAL;
	}

	if (in_width > maxsinglelinewidth && *five_taps) {
		DSSERR("cannot setup scaling with five taps");
		return -EINVAL;
	}
	return 0;
}