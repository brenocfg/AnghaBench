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
typedef  scalar_t__ u16 ;
struct TYPE_3__ {void* a3; void* a2; void* a1; void* a0; } ;
struct ssb_sprom {int revision; TYPE_1__ antenna_gain; int /*<<< orphan*/  il0mac; scalar_t__ const* core_pwr_info; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pa_5gh; int /*<<< orphan*/ * pa_5g; int /*<<< orphan*/ * pa_5gl; int /*<<< orphan*/  maxpwr_5gl; int /*<<< orphan*/  maxpwr_5gh; int /*<<< orphan*/  maxpwr_5g; int /*<<< orphan*/  itssi_5g; int /*<<< orphan*/ * pa_2g; int /*<<< orphan*/  maxpwr_2g; int /*<<< orphan*/  itssi_2g; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__ const*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  SPEX (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 size_t SPOFF (scalar_t__) ; 
 scalar_t__ SSB_SPROM1_SPID ; 
 int SSB_SPROM4_2G_ITSSI ; 
 int SSB_SPROM4_2G_ITSSI_SHIFT ; 
 int SSB_SPROM4_2G_MAXP ; 
 scalar_t__ SSB_SPROM4_2G_MAXP_ITSSI ; 
 scalar_t__ SSB_SPROM4_2G_PA_0 ; 
 scalar_t__ SSB_SPROM4_2G_PA_1 ; 
 scalar_t__ SSB_SPROM4_2G_PA_2 ; 
 scalar_t__ SSB_SPROM4_2G_PA_3 ; 
 scalar_t__ SSB_SPROM4_5GHL_MAXP ; 
 int SSB_SPROM4_5GH_MAXP ; 
 scalar_t__ SSB_SPROM4_5GH_PA_0 ; 
 scalar_t__ SSB_SPROM4_5GH_PA_1 ; 
 scalar_t__ SSB_SPROM4_5GH_PA_2 ; 
 scalar_t__ SSB_SPROM4_5GH_PA_3 ; 
 int SSB_SPROM4_5GL_MAXP ; 
 int SSB_SPROM4_5GL_MAXP_SHIFT ; 
 scalar_t__ SSB_SPROM4_5GL_PA_0 ; 
 scalar_t__ SSB_SPROM4_5GL_PA_1 ; 
 scalar_t__ SSB_SPROM4_5GL_PA_2 ; 
 scalar_t__ SSB_SPROM4_5GL_PA_3 ; 
 int SSB_SPROM4_5G_ITSSI ; 
 int SSB_SPROM4_5G_ITSSI_SHIFT ; 
 int SSB_SPROM4_5G_MAXP ; 
 scalar_t__ SSB_SPROM4_5G_MAXP_ITSSI ; 
 scalar_t__ SSB_SPROM4_5G_PA_0 ; 
 scalar_t__ SSB_SPROM4_5G_PA_1 ; 
 scalar_t__ SSB_SPROM4_5G_PA_2 ; 
 scalar_t__ SSB_SPROM4_5G_PA_3 ; 
 int /*<<< orphan*/  SSB_SPROM4_AGAIN0 ; 
 int /*<<< orphan*/  SSB_SPROM4_AGAIN01 ; 
 int /*<<< orphan*/  SSB_SPROM4_AGAIN0_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_AGAIN1 ; 
 int /*<<< orphan*/  SSB_SPROM4_AGAIN1_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_AGAIN2 ; 
 int /*<<< orphan*/  SSB_SPROM4_AGAIN23 ; 
 int /*<<< orphan*/  SSB_SPROM4_AGAIN2_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_AGAIN3 ; 
 int /*<<< orphan*/  SSB_SPROM4_AGAIN3_SHIFT ; 
 scalar_t__ SSB_SPROM4_ANTAVAIL ; 
 int SSB_SPROM4_ANTAVAIL_A ; 
 int SSB_SPROM4_ANTAVAIL_A_SHIFT ; 
 int SSB_SPROM4_ANTAVAIL_BG ; 
 int SSB_SPROM4_ANTAVAIL_BG_SHIFT ; 
 scalar_t__ SSB_SPROM4_BFL2HI ; 
 scalar_t__ SSB_SPROM4_BFL2LO ; 
 scalar_t__ SSB_SPROM4_BFLHI ; 
 scalar_t__ SSB_SPROM4_BFLLO ; 
 scalar_t__ SSB_SPROM4_BOARDREV ; 
 scalar_t__ SSB_SPROM4_CCODE ; 
 scalar_t__ SSB_SPROM4_ETHPHY ; 
 int SSB_SPROM4_ETHPHY_ET0A ; 
 int SSB_SPROM4_ETHPHY_ET1A ; 
 int SSB_SPROM4_ETHPHY_ET1A_SHIFT ; 
 scalar_t__ SSB_SPROM4_GPIOA ; 
 int SSB_SPROM4_GPIOA_P0 ; 
 int SSB_SPROM4_GPIOA_P1 ; 
 int SSB_SPROM4_GPIOA_P1_SHIFT ; 
 scalar_t__ SSB_SPROM4_GPIOB ; 
 int SSB_SPROM4_GPIOB_P2 ; 
 int SSB_SPROM4_GPIOB_P3 ; 
 int SSB_SPROM4_GPIOB_P3_SHIFT ; 
 scalar_t__ SSB_SPROM4_IL0MAC ; 
 int SSB_SPROM4_ITSSI_A ; 
 int SSB_SPROM4_ITSSI_A_SHIFT ; 
 int SSB_SPROM4_ITSSI_BG ; 
 int SSB_SPROM4_ITSSI_BG_SHIFT ; 
 scalar_t__ SSB_SPROM4_MAXP_A ; 
 int SSB_SPROM4_MAXP_A_MASK ; 
 scalar_t__ SSB_SPROM4_MAXP_BG ; 
 int SSB_SPROM4_MAXP_BG_MASK ; 
#define  SSB_SPROM4_PWR_INFO_CORE0 131 
#define  SSB_SPROM4_PWR_INFO_CORE1 130 
#define  SSB_SPROM4_PWR_INFO_CORE2 129 
#define  SSB_SPROM4_PWR_INFO_CORE3 128 
 scalar_t__ SSB_SPROM5_BFL2HI ; 
 scalar_t__ SSB_SPROM5_BFL2LO ; 
 scalar_t__ SSB_SPROM5_BFLHI ; 
 scalar_t__ SSB_SPROM5_BFLLO ; 
 scalar_t__ SSB_SPROM5_CCODE ; 
 scalar_t__ SSB_SPROM5_GPIOA ; 
 int SSB_SPROM5_GPIOA_P0 ; 
 int SSB_SPROM5_GPIOA_P1 ; 
 int SSB_SPROM5_GPIOA_P1_SHIFT ; 
 scalar_t__ SSB_SPROM5_GPIOB ; 
 int SSB_SPROM5_GPIOB_P2 ; 
 int SSB_SPROM5_GPIOB_P3 ; 
 int SSB_SPROM5_GPIOB_P3_SHIFT ; 
 scalar_t__ SSB_SPROM5_IL0MAC ; 
 int /*<<< orphan*/ * alpha2 ; 
 int /*<<< orphan*/  ant_available_a ; 
 int /*<<< orphan*/  ant_available_bg ; 
 int /*<<< orphan*/  board_rev ; 
 int /*<<< orphan*/  board_type ; 
 int /*<<< orphan*/  boardflags2_hi ; 
 int /*<<< orphan*/  boardflags2_lo ; 
 int /*<<< orphan*/  boardflags_hi ; 
 int /*<<< orphan*/  boardflags_lo ; 
 TYPE_2__* core_pwr_info ; 
 int /*<<< orphan*/  et0phyaddr ; 
 int /*<<< orphan*/  et1phyaddr ; 
 int /*<<< orphan*/  gpio0 ; 
 int /*<<< orphan*/  gpio1 ; 
 int /*<<< orphan*/  gpio2 ; 
 int /*<<< orphan*/  gpio3 ; 
 int /*<<< orphan*/  itssi_a ; 
 int /*<<< orphan*/  itssi_bg ; 
 int /*<<< orphan*/  maxpwr_a ; 
 int /*<<< orphan*/  maxpwr_bg ; 
 void* sprom_extract_antgain (int,scalar_t__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprom_extract_r458 (struct ssb_sprom*,scalar_t__ const*) ; 
 int /*<<< orphan*/  sprom_get_mac (int /*<<< orphan*/ ,scalar_t__ const*) ; 

__attribute__((used)) static void sprom_extract_r45(struct ssb_sprom *out, const u16 *in)
{
	static const u16 pwr_info_offset[] = {
		SSB_SPROM4_PWR_INFO_CORE0, SSB_SPROM4_PWR_INFO_CORE1,
		SSB_SPROM4_PWR_INFO_CORE2, SSB_SPROM4_PWR_INFO_CORE3
	};
	u16 il0mac_offset;
	int i;

	BUILD_BUG_ON(ARRAY_SIZE(pwr_info_offset) !=
		     ARRAY_SIZE(out->core_pwr_info));

	if (out->revision == 4)
		il0mac_offset = SSB_SPROM4_IL0MAC;
	else
		il0mac_offset = SSB_SPROM5_IL0MAC;

	sprom_get_mac(out->il0mac, &in[SPOFF(il0mac_offset)]);

	SPEX(et0phyaddr, SSB_SPROM4_ETHPHY, SSB_SPROM4_ETHPHY_ET0A, 0);
	SPEX(et1phyaddr, SSB_SPROM4_ETHPHY, SSB_SPROM4_ETHPHY_ET1A,
	     SSB_SPROM4_ETHPHY_ET1A_SHIFT);
	SPEX(board_rev, SSB_SPROM4_BOARDREV, 0xFFFF, 0);
	SPEX(board_type, SSB_SPROM1_SPID, 0xFFFF, 0);
	if (out->revision == 4) {
		SPEX(alpha2[0], SSB_SPROM4_CCODE, 0xff00, 8);
		SPEX(alpha2[1], SSB_SPROM4_CCODE, 0x00ff, 0);
		SPEX(boardflags_lo, SSB_SPROM4_BFLLO, 0xFFFF, 0);
		SPEX(boardflags_hi, SSB_SPROM4_BFLHI, 0xFFFF, 0);
		SPEX(boardflags2_lo, SSB_SPROM4_BFL2LO, 0xFFFF, 0);
		SPEX(boardflags2_hi, SSB_SPROM4_BFL2HI, 0xFFFF, 0);
	} else {
		SPEX(alpha2[0], SSB_SPROM5_CCODE, 0xff00, 8);
		SPEX(alpha2[1], SSB_SPROM5_CCODE, 0x00ff, 0);
		SPEX(boardflags_lo, SSB_SPROM5_BFLLO, 0xFFFF, 0);
		SPEX(boardflags_hi, SSB_SPROM5_BFLHI, 0xFFFF, 0);
		SPEX(boardflags2_lo, SSB_SPROM5_BFL2LO, 0xFFFF, 0);
		SPEX(boardflags2_hi, SSB_SPROM5_BFL2HI, 0xFFFF, 0);
	}
	SPEX(ant_available_a, SSB_SPROM4_ANTAVAIL, SSB_SPROM4_ANTAVAIL_A,
	     SSB_SPROM4_ANTAVAIL_A_SHIFT);
	SPEX(ant_available_bg, SSB_SPROM4_ANTAVAIL, SSB_SPROM4_ANTAVAIL_BG,
	     SSB_SPROM4_ANTAVAIL_BG_SHIFT);
	SPEX(maxpwr_bg, SSB_SPROM4_MAXP_BG, SSB_SPROM4_MAXP_BG_MASK, 0);
	SPEX(itssi_bg, SSB_SPROM4_MAXP_BG, SSB_SPROM4_ITSSI_BG,
	     SSB_SPROM4_ITSSI_BG_SHIFT);
	SPEX(maxpwr_a, SSB_SPROM4_MAXP_A, SSB_SPROM4_MAXP_A_MASK, 0);
	SPEX(itssi_a, SSB_SPROM4_MAXP_A, SSB_SPROM4_ITSSI_A,
	     SSB_SPROM4_ITSSI_A_SHIFT);
	if (out->revision == 4) {
		SPEX(gpio0, SSB_SPROM4_GPIOA, SSB_SPROM4_GPIOA_P0, 0);
		SPEX(gpio1, SSB_SPROM4_GPIOA, SSB_SPROM4_GPIOA_P1,
		     SSB_SPROM4_GPIOA_P1_SHIFT);
		SPEX(gpio2, SSB_SPROM4_GPIOB, SSB_SPROM4_GPIOB_P2, 0);
		SPEX(gpio3, SSB_SPROM4_GPIOB, SSB_SPROM4_GPIOB_P3,
		     SSB_SPROM4_GPIOB_P3_SHIFT);
	} else {
		SPEX(gpio0, SSB_SPROM5_GPIOA, SSB_SPROM5_GPIOA_P0, 0);
		SPEX(gpio1, SSB_SPROM5_GPIOA, SSB_SPROM5_GPIOA_P1,
		     SSB_SPROM5_GPIOA_P1_SHIFT);
		SPEX(gpio2, SSB_SPROM5_GPIOB, SSB_SPROM5_GPIOB_P2, 0);
		SPEX(gpio3, SSB_SPROM5_GPIOB, SSB_SPROM5_GPIOB_P3,
		     SSB_SPROM5_GPIOB_P3_SHIFT);
	}

	/* Extract the antenna gain values. */
	out->antenna_gain.a0 = sprom_extract_antgain(out->revision, in,
						     SSB_SPROM4_AGAIN01,
						     SSB_SPROM4_AGAIN0,
						     SSB_SPROM4_AGAIN0_SHIFT);
	out->antenna_gain.a1 = sprom_extract_antgain(out->revision, in,
						     SSB_SPROM4_AGAIN01,
						     SSB_SPROM4_AGAIN1,
						     SSB_SPROM4_AGAIN1_SHIFT);
	out->antenna_gain.a2 = sprom_extract_antgain(out->revision, in,
						     SSB_SPROM4_AGAIN23,
						     SSB_SPROM4_AGAIN2,
						     SSB_SPROM4_AGAIN2_SHIFT);
	out->antenna_gain.a3 = sprom_extract_antgain(out->revision, in,
						     SSB_SPROM4_AGAIN23,
						     SSB_SPROM4_AGAIN3,
						     SSB_SPROM4_AGAIN3_SHIFT);

	/* Extract cores power info info */
	for (i = 0; i < ARRAY_SIZE(pwr_info_offset); i++) {
		u16 o = pwr_info_offset[i];

		SPEX(core_pwr_info[i].itssi_2g, o + SSB_SPROM4_2G_MAXP_ITSSI,
			SSB_SPROM4_2G_ITSSI, SSB_SPROM4_2G_ITSSI_SHIFT);
		SPEX(core_pwr_info[i].maxpwr_2g, o + SSB_SPROM4_2G_MAXP_ITSSI,
			SSB_SPROM4_2G_MAXP, 0);

		SPEX(core_pwr_info[i].pa_2g[0], o + SSB_SPROM4_2G_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_2g[1], o + SSB_SPROM4_2G_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_2g[2], o + SSB_SPROM4_2G_PA_2, ~0, 0);
		SPEX(core_pwr_info[i].pa_2g[3], o + SSB_SPROM4_2G_PA_3, ~0, 0);

		SPEX(core_pwr_info[i].itssi_5g, o + SSB_SPROM4_5G_MAXP_ITSSI,
			SSB_SPROM4_5G_ITSSI, SSB_SPROM4_5G_ITSSI_SHIFT);
		SPEX(core_pwr_info[i].maxpwr_5g, o + SSB_SPROM4_5G_MAXP_ITSSI,
			SSB_SPROM4_5G_MAXP, 0);
		SPEX(core_pwr_info[i].maxpwr_5gh, o + SSB_SPROM4_5GHL_MAXP,
			SSB_SPROM4_5GH_MAXP, 0);
		SPEX(core_pwr_info[i].maxpwr_5gl, o + SSB_SPROM4_5GHL_MAXP,
			SSB_SPROM4_5GL_MAXP, SSB_SPROM4_5GL_MAXP_SHIFT);

		SPEX(core_pwr_info[i].pa_5gl[0], o + SSB_SPROM4_5GL_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gl[1], o + SSB_SPROM4_5GL_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gl[2], o + SSB_SPROM4_5GL_PA_2, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gl[3], o + SSB_SPROM4_5GL_PA_3, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[0], o + SSB_SPROM4_5G_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[1], o + SSB_SPROM4_5G_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[2], o + SSB_SPROM4_5G_PA_2, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[3], o + SSB_SPROM4_5G_PA_3, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[0], o + SSB_SPROM4_5GH_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[1], o + SSB_SPROM4_5GH_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[2], o + SSB_SPROM4_5GH_PA_2, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[3], o + SSB_SPROM4_5GH_PA_3, ~0, 0);
	}

	sprom_extract_r458(out, in);

	/* TODO - get remaining rev 4 stuff needed */
}