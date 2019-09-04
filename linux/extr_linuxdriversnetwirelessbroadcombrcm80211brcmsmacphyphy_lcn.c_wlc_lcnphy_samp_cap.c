#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int val ;
typedef  int u32 ;
typedef  int u16 ;
struct brcms_phy_lcnphy {scalar_t__ lcnphy_iqcal_swp_dis; } ;
struct TYPE_2__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {int /*<<< orphan*/  d11core; TYPE_1__ u; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int bcma_read16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_write16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcma_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  psm_corectlsts ; 
 int /*<<< orphan*/  psm_phy_hdr_param ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  smpl_clct_curptr ; 
 int /*<<< orphan*/  smpl_clct_stpptr ; 
 int /*<<< orphan*/  smpl_clct_strptr ; 
 int /*<<< orphan*/  tplatewrdata ; 
 int /*<<< orphan*/  tplatewrptr ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void
wlc_lcnphy_samp_cap(struct brcms_phy *pi, int clip_detect_algo, u16 thresh,
		    s16 *ptr, int mode)
{
	u32 curval1, curval2, stpptr, curptr, strptr, val;
	u16 sslpnCalibClkEnCtrl, timer;
	u16 old_sslpnCalibClkEnCtrl;
	s16 imag, real;
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

	timer = 0;
	old_sslpnCalibClkEnCtrl = read_phy_reg(pi, 0x6da);

	curval1 = bcma_read16(pi->d11core, D11REGOFFS(psm_corectlsts));
	ptr[130] = 0;
	bcma_write16(pi->d11core, D11REGOFFS(psm_corectlsts),
		     ((1 << 6) | curval1));

	bcma_write16(pi->d11core, D11REGOFFS(smpl_clct_strptr), 0x7E00);
	bcma_write16(pi->d11core, D11REGOFFS(smpl_clct_stpptr), 0x8000);
	udelay(20);
	curval2 = bcma_read16(pi->d11core, D11REGOFFS(psm_phy_hdr_param));
	bcma_write16(pi->d11core, D11REGOFFS(psm_phy_hdr_param),
		     curval2 | 0x30);

	write_phy_reg(pi, 0x555, 0x0);
	write_phy_reg(pi, 0x5a6, 0x5);

	write_phy_reg(pi, 0x5a2, (u16) (mode | mode << 6));
	write_phy_reg(pi, 0x5cf, 3);
	write_phy_reg(pi, 0x5a5, 0x3);
	write_phy_reg(pi, 0x583, 0x0);
	write_phy_reg(pi, 0x584, 0x0);
	write_phy_reg(pi, 0x585, 0x0fff);
	write_phy_reg(pi, 0x586, 0x0000);

	write_phy_reg(pi, 0x580, 0x4501);

	sslpnCalibClkEnCtrl = read_phy_reg(pi, 0x6da);
	write_phy_reg(pi, 0x6da, (u32) (sslpnCalibClkEnCtrl | 0x2008));
	stpptr = bcma_read16(pi->d11core, D11REGOFFS(smpl_clct_stpptr));
	curptr = bcma_read16(pi->d11core, D11REGOFFS(smpl_clct_curptr));
	do {
		udelay(10);
		curptr = bcma_read16(pi->d11core, D11REGOFFS(smpl_clct_curptr));
		timer++;
	} while ((curptr != stpptr) && (timer < 500));

	bcma_write16(pi->d11core, D11REGOFFS(psm_phy_hdr_param), 0x2);
	strptr = 0x7E00;
	bcma_write32(pi->d11core, D11REGOFFS(tplatewrptr), strptr);
	while (strptr < 0x8000) {
		val = bcma_read32(pi->d11core, D11REGOFFS(tplatewrdata));
		imag = ((val >> 16) & 0x3ff);
		real = ((val) & 0x3ff);
		if (imag > 511)
			imag -= 1024;

		if (real > 511)
			real -= 1024;

		if (pi_lcn->lcnphy_iqcal_swp_dis)
			ptr[(strptr - 0x7E00) / 4] = real;
		else
			ptr[(strptr - 0x7E00) / 4] = imag;

		if (clip_detect_algo) {
			if (imag > thresh || imag < -thresh) {
				strptr = 0x8000;
				ptr[130] = 1;
			}
		}

		strptr += 4;
	}

	write_phy_reg(pi, 0x6da, old_sslpnCalibClkEnCtrl);
	bcma_write16(pi->d11core, D11REGOFFS(psm_phy_hdr_param), curval2);
	bcma_write16(pi->d11core, D11REGOFFS(psm_corectlsts), curval1);
}