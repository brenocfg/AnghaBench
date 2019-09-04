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
typedef  int u16 ;
struct b43_wldev {int dummy; } ;
typedef  enum n_rssi_type { ____Placeholder_n_rssi_type } n_rssi_type ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_AFECTL_C1 ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_C2 ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_OVER ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_CMD ; 
 int B43_NPHY_RFCTL_CMD_CORESEL ; 
 int B43_NPHY_RFCTL_CMD_CORESEL_SHIFT ; 
 int B43_NPHY_RFCTL_CMD_RXEN ; 
 int B43_NPHY_RFCTL_CMD_START ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_OVER ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_RSSIO1 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_RSSIO2 ; 
#define  N_RSSI_IQ 132 
#define  N_RSSI_NB 131 
#define  N_RSSI_TBD 130 
#define  N_RSSI_W1 129 
#define  N_RSSI_W2 128 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43_nphy_rev2_rssi_select(struct b43_wldev *dev, u8 code,
				      enum n_rssi_type rssi_type)
{
	u16 val;
	bool rssi_w1_w2_nb = false;

	switch (rssi_type) {
	case N_RSSI_W1:
	case N_RSSI_W2:
	case N_RSSI_NB:
		val = 0;
		rssi_w1_w2_nb = true;
		break;
	case N_RSSI_TBD:
		val = 1;
		break;
	case N_RSSI_IQ:
		val = 2;
		break;
	default:
		val = 3;
	}

	val = (val << 12) | (val << 14);
	b43_phy_maskset(dev, B43_NPHY_AFECTL_C1, 0x0FFF, val);
	b43_phy_maskset(dev, B43_NPHY_AFECTL_C2, 0x0FFF, val);

	if (rssi_w1_w2_nb) {
		b43_phy_maskset(dev, B43_NPHY_RFCTL_RSSIO1, 0xFFCF,
				(rssi_type + 1) << 4);
		b43_phy_maskset(dev, B43_NPHY_RFCTL_RSSIO2, 0xFFCF,
				(rssi_type + 1) << 4);
	}

	if (code == 0) {
		b43_phy_mask(dev, B43_NPHY_AFECTL_OVER, ~0x3000);
		if (rssi_w1_w2_nb) {
			b43_phy_mask(dev, B43_NPHY_RFCTL_CMD,
				~(B43_NPHY_RFCTL_CMD_RXEN |
				  B43_NPHY_RFCTL_CMD_CORESEL));
			b43_phy_mask(dev, B43_NPHY_RFCTL_OVER,
				~(0x1 << 12 |
				  0x1 << 5 |
				  0x1 << 1 |
				  0x1));
			b43_phy_mask(dev, B43_NPHY_RFCTL_CMD,
				~B43_NPHY_RFCTL_CMD_START);
			udelay(20);
			b43_phy_mask(dev, B43_NPHY_RFCTL_OVER, ~0x1);
		}
	} else {
		b43_phy_set(dev, B43_NPHY_AFECTL_OVER, 0x3000);
		if (rssi_w1_w2_nb) {
			b43_phy_maskset(dev, B43_NPHY_RFCTL_CMD,
				~(B43_NPHY_RFCTL_CMD_RXEN |
				  B43_NPHY_RFCTL_CMD_CORESEL),
				(B43_NPHY_RFCTL_CMD_RXEN |
				 code << B43_NPHY_RFCTL_CMD_CORESEL_SHIFT));
			b43_phy_set(dev, B43_NPHY_RFCTL_OVER,
				(0x1 << 12 |
				  0x1 << 5 |
				  0x1 << 1 |
				  0x1));
			b43_phy_set(dev, B43_NPHY_RFCTL_CMD,
				B43_NPHY_RFCTL_CMD_START);
			udelay(20);
			b43_phy_mask(dev, B43_NPHY_RFCTL_OVER, ~0x1);
		}
	}
}