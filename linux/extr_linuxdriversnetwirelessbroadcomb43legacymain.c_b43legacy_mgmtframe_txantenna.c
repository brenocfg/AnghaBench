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
typedef  int u16 ;
struct b43legacy_wldev {int dummy; } ;

/* Variables and functions */
#define  B43legacy_ANTENNA0 130 
#define  B43legacy_ANTENNA1 129 
#define  B43legacy_ANTENNA_AUTO 128 
 int /*<<< orphan*/  B43legacy_BUG_ON (int) ; 
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int /*<<< orphan*/  B43legacy_SHM_SH_ACKCTSPHYCTL ; 
 int /*<<< orphan*/  B43legacy_SHM_SH_BEACPHYCTL ; 
 int /*<<< orphan*/  B43legacy_SHM_SH_PRPHYCTL ; 
 int B43legacy_TX4_PHY_ANT ; 
 int B43legacy_TX4_PHY_ANT0 ; 
 int B43legacy_TX4_PHY_ANT1 ; 
 int B43legacy_TX4_PHY_ANTLAST ; 
 int b43legacy_shm_read16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_shm_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43legacy_mgmtframe_txantenna(struct b43legacy_wldev *dev,
					  int antenna)
{
	u16 ant = 0;
	u16 tmp;

	switch (antenna) {
	case B43legacy_ANTENNA0:
		ant |= B43legacy_TX4_PHY_ANT0;
		break;
	case B43legacy_ANTENNA1:
		ant |= B43legacy_TX4_PHY_ANT1;
		break;
	case B43legacy_ANTENNA_AUTO:
		ant |= B43legacy_TX4_PHY_ANTLAST;
		break;
	default:
		B43legacy_BUG_ON(1);
	}

	/* FIXME We also need to set the other flags of the PHY control
	 * field somewhere. */

	/* For Beacons */
	tmp = b43legacy_shm_read16(dev, B43legacy_SHM_SHARED,
				   B43legacy_SHM_SH_BEACPHYCTL);
	tmp = (tmp & ~B43legacy_TX4_PHY_ANT) | ant;
	b43legacy_shm_write16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_BEACPHYCTL, tmp);
	/* For ACK/CTS */
	tmp = b43legacy_shm_read16(dev, B43legacy_SHM_SHARED,
				   B43legacy_SHM_SH_ACKCTSPHYCTL);
	tmp = (tmp & ~B43legacy_TX4_PHY_ANT) | ant;
	b43legacy_shm_write16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_ACKCTSPHYCTL, tmp);
	/* For Probe Resposes */
	tmp = b43legacy_shm_read16(dev, B43legacy_SHM_SHARED,
				   B43legacy_SHM_SH_PRPHYCTL);
	tmp = (tmp & ~B43legacy_TX4_PHY_ANT) | ant;
	b43legacy_shm_write16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_PRPHYCTL, tmp);
}