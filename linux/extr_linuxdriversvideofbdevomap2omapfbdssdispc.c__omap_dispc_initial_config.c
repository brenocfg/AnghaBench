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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* feat; int /*<<< orphan*/  core_clk_rate; } ;
struct TYPE_3__ {scalar_t__ mstandby_workaround; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_CONFIG ; 
 int /*<<< orphan*/  DISPC_DIVISOR ; 
 int /*<<< orphan*/  DISPC_MSTANDBY_CTRL ; 
 int /*<<< orphan*/  FEAT_CORE_CLK_DIV ; 
 int /*<<< orphan*/  FEAT_FUNCGATED ; 
 int /*<<< orphan*/  FEAT_MFLAG ; 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  OMAP_DSS_LOAD_FRAME_ONLY ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 TYPE_2__ dispc ; 
 int /*<<< orphan*/  dispc_configure_burst_sizes () ; 
 int /*<<< orphan*/  dispc_fclk_rate () ; 
 int /*<<< orphan*/  dispc_init_fifos () ; 
 int /*<<< orphan*/  dispc_init_mflag () ; 
 int /*<<< orphan*/  dispc_ovl_enable_zorder_planes () ; 
 int /*<<< orphan*/  dispc_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_set_loadmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_setup_color_conv_coef () ; 
 int /*<<< orphan*/  dispc_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _omap_dispc_initial_config(void)
{
	u32 l;

	/* Exclusively enable DISPC_CORE_CLK and set divider to 1 */
	if (dss_has_feature(FEAT_CORE_CLK_DIV)) {
		l = dispc_read_reg(DISPC_DIVISOR);
		/* Use DISPC_DIVISOR.LCD, instead of DISPC_DIVISOR1.LCD */
		l = FLD_MOD(l, 1, 0, 0);
		l = FLD_MOD(l, 1, 23, 16);
		dispc_write_reg(DISPC_DIVISOR, l);

		dispc.core_clk_rate = dispc_fclk_rate();
	}

	/* FUNCGATED */
	if (dss_has_feature(FEAT_FUNCGATED))
		REG_FLD_MOD(DISPC_CONFIG, 1, 9, 9);

	dispc_setup_color_conv_coef();

	dispc_set_loadmode(OMAP_DSS_LOAD_FRAME_ONLY);

	dispc_init_fifos();

	dispc_configure_burst_sizes();

	dispc_ovl_enable_zorder_planes();

	if (dispc.feat->mstandby_workaround)
		REG_FLD_MOD(DISPC_MSTANDBY_CTRL, 1, 0, 0);

	if (dss_has_feature(FEAT_MFLAG))
		dispc_init_mflag();
}