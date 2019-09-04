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
typedef  int u8 ;
typedef  int u32 ;
struct ofdm_phy_hdr {int dummy; } ;

/* Variables and functions */
 int BRCMS_RATE_MASK ; 
 int /*<<< orphan*/  D11A_PHY_HDR_SRATE (struct ofdm_phy_hdr*,int) ; 
 int /*<<< orphan*/  D11_PHY_HDR_LEN ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* rate_info ; 
 int rspec2rate (int) ; 

__attribute__((used)) static void
brcms_c_compute_ofdm_plcp(u32 rspec, u32 length, u8 *plcp)
{
	u8 rate_signal;
	u32 tmp = 0;
	int rate = rspec2rate(rspec);

	/*
	 * encode rate per 802.11a-1999 sec 17.3.4.1, with lsb
	 * transmitted first
	 */
	rate_signal = rate_info[rate] & BRCMS_RATE_MASK;
	memset(plcp, 0, D11_PHY_HDR_LEN);
	D11A_PHY_HDR_SRATE((struct ofdm_phy_hdr *) plcp, rate_signal);

	tmp = (length & 0xfff) << 5;
	plcp[2] |= (tmp >> 16) & 0xff;
	plcp[1] |= (tmp >> 8) & 0xff;
	plcp[0] |= tmp & 0xff;
}