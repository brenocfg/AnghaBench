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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct brcms_phy {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 scalar_t__ NPHY_RAIL_I ; 
 scalar_t__ NPHY_RAIL_Q ; 
 int NPHY_RSSICAL_MAXREAD ; 
 scalar_t__ NPHY_RSSI_SEL_IQ ; 
 scalar_t__ NPHY_RSSI_SEL_NB ; 
 scalar_t__ NPHY_RSSI_SEL_TBD ; 
 scalar_t__ NPHY_RSSI_SEL_TSSI_2G ; 
 scalar_t__ NPHY_RSSI_SEL_TSSI_5G ; 
 scalar_t__ NPHY_RSSI_SEL_W1 ; 
 scalar_t__ NPHY_RSSI_SEL_W2 ; 
 scalar_t__ RADIO_MIMO_CORESEL_ALLRX ; 
 scalar_t__ RADIO_MIMO_CORESEL_CORE1 ; 
 scalar_t__ RADIO_MIMO_CORESEL_CORE2 ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void
wlc_phy_scale_offset_rssi_nphy(struct brcms_phy *pi, u16 scale, s8 offset,
			       u8 coresel, u8 rail, u8 rssi_type)
{
	u16 valuetostuff;

	offset = (offset > NPHY_RSSICAL_MAXREAD) ?
		 NPHY_RSSICAL_MAXREAD : offset;
	offset = (offset < (-NPHY_RSSICAL_MAXREAD - 1)) ?
		 -NPHY_RSSICAL_MAXREAD - 1 : offset;

	valuetostuff = ((scale & 0x3f) << 8) | (offset & 0x3f);

	if (((coresel == RADIO_MIMO_CORESEL_CORE1) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_I) && (rssi_type == NPHY_RSSI_SEL_NB))
		write_phy_reg(pi, 0x1a6, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE1) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_Q) && (rssi_type == NPHY_RSSI_SEL_NB))
		write_phy_reg(pi, 0x1ac, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE2) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_I) && (rssi_type == NPHY_RSSI_SEL_NB))
		write_phy_reg(pi, 0x1b2, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE2) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_Q) && (rssi_type == NPHY_RSSI_SEL_NB))
		write_phy_reg(pi, 0x1b8, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE1) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_I) && (rssi_type == NPHY_RSSI_SEL_W1))
		write_phy_reg(pi, 0x1a4, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE1) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_Q) && (rssi_type == NPHY_RSSI_SEL_W1))
		write_phy_reg(pi, 0x1aa, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE2) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_I) && (rssi_type == NPHY_RSSI_SEL_W1))
		write_phy_reg(pi, 0x1b0, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE2) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_Q) && (rssi_type == NPHY_RSSI_SEL_W1))
		write_phy_reg(pi, 0x1b6, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE1) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_I) && (rssi_type == NPHY_RSSI_SEL_W2))
		write_phy_reg(pi, 0x1a5, valuetostuff);
	if (((coresel == RADIO_MIMO_CORESEL_CORE1) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_Q) && (rssi_type == NPHY_RSSI_SEL_W2))
		write_phy_reg(pi, 0x1ab, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE2) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_I) && (rssi_type == NPHY_RSSI_SEL_W2))
		write_phy_reg(pi, 0x1b1, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE2) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_Q) && (rssi_type == NPHY_RSSI_SEL_W2))
		write_phy_reg(pi, 0x1b7, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE1) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_I) && (rssi_type == NPHY_RSSI_SEL_TBD))
		write_phy_reg(pi, 0x1a7, valuetostuff);
	if (((coresel == RADIO_MIMO_CORESEL_CORE1) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_Q) && (rssi_type == NPHY_RSSI_SEL_TBD))
		write_phy_reg(pi, 0x1ad, valuetostuff);
	if (((coresel == RADIO_MIMO_CORESEL_CORE2) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_I) && (rssi_type == NPHY_RSSI_SEL_TBD))
		write_phy_reg(pi, 0x1b3, valuetostuff);
	if (((coresel == RADIO_MIMO_CORESEL_CORE2) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_Q) && (rssi_type == NPHY_RSSI_SEL_TBD))
		write_phy_reg(pi, 0x1b9, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE1) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_I) && (rssi_type == NPHY_RSSI_SEL_IQ))
		write_phy_reg(pi, 0x1a8, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE1) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_Q) && (rssi_type == NPHY_RSSI_SEL_IQ))
		write_phy_reg(pi, 0x1ae, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE2) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_I) && (rssi_type == NPHY_RSSI_SEL_IQ))
		write_phy_reg(pi, 0x1b4, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE2) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rail == NPHY_RAIL_Q) && (rssi_type == NPHY_RSSI_SEL_IQ))
		write_phy_reg(pi, 0x1ba, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE1) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rssi_type == NPHY_RSSI_SEL_TSSI_2G))
		write_phy_reg(pi, 0x1a9, valuetostuff);
	if (((coresel == RADIO_MIMO_CORESEL_CORE2) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rssi_type == NPHY_RSSI_SEL_TSSI_2G))
		write_phy_reg(pi, 0x1b5, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE1) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rssi_type == NPHY_RSSI_SEL_TSSI_5G))
		write_phy_reg(pi, 0x1af, valuetostuff);

	if (((coresel == RADIO_MIMO_CORESEL_CORE2) ||
	     (coresel == RADIO_MIMO_CORESEL_ALLRX)) &&
	    (rssi_type == NPHY_RSSI_SEL_TSSI_5G))
		write_phy_reg(pi, 0x1bb, valuetostuff);
}