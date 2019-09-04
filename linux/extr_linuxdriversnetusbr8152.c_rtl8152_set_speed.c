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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ supports_gmii; } ;
struct r8152 {int version; TYPE_1__ mii; int /*<<< orphan*/  flags; } ;
typedef  enum spd_duplex { ____Placeholder_spd_duplex } spd_duplex ;

/* Variables and functions */
 scalar_t__ ADVERTISE_1000FULL ; 
 scalar_t__ ADVERTISE_1000HALF ; 
 scalar_t__ ADVERTISE_100FULL ; 
 scalar_t__ ADVERTISE_100HALF ; 
 scalar_t__ ADVERTISE_10FULL ; 
 scalar_t__ ADVERTISE_10HALF ; 
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ BMCR_ANENABLE ; 
 scalar_t__ BMCR_ANRESTART ; 
 scalar_t__ BMCR_FULLDPLX ; 
 scalar_t__ BMCR_RESET ; 
 scalar_t__ BMCR_SPEED100 ; 
 scalar_t__ BMCR_SPEED1000 ; 
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
 int FORCE_100M_HALF ; 
 int FORCE_10M_HALF ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int NWAY_1000M_FULL ; 
 int NWAY_100M_FULL ; 
 int NWAY_100M_HALF ; 
 int NWAY_10M_FULL ; 
 int NWAY_10M_HALF ; 
 int /*<<< orphan*/  PHY_RESET ; 
#define  RTL_VER_08 129 
#define  RTL_VER_09 128 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  UPS_FLAGS_SPEED_MASK ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ r8152_mdio_read (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8152_mdio_write (struct r8152*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  r8153b_ups_flags_w1w0 (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ups_flags_speed (int) ; 

__attribute__((used)) static int rtl8152_set_speed(struct r8152 *tp, u8 autoneg, u16 speed, u8 duplex)
{
	u16 bmcr, anar, gbcr;
	enum spd_duplex speed_duplex;
	int ret = 0;

	anar = r8152_mdio_read(tp, MII_ADVERTISE);
	anar &= ~(ADVERTISE_10HALF | ADVERTISE_10FULL |
		  ADVERTISE_100HALF | ADVERTISE_100FULL);
	if (tp->mii.supports_gmii) {
		gbcr = r8152_mdio_read(tp, MII_CTRL1000);
		gbcr &= ~(ADVERTISE_1000FULL | ADVERTISE_1000HALF);
	} else {
		gbcr = 0;
	}

	if (autoneg == AUTONEG_DISABLE) {
		if (speed == SPEED_10) {
			bmcr = 0;
			anar |= ADVERTISE_10HALF | ADVERTISE_10FULL;
			speed_duplex = FORCE_10M_HALF;
		} else if (speed == SPEED_100) {
			bmcr = BMCR_SPEED100;
			anar |= ADVERTISE_100HALF | ADVERTISE_100FULL;
			speed_duplex = FORCE_100M_HALF;
		} else if (speed == SPEED_1000 && tp->mii.supports_gmii) {
			bmcr = BMCR_SPEED1000;
			gbcr |= ADVERTISE_1000FULL | ADVERTISE_1000HALF;
			speed_duplex = NWAY_1000M_FULL;
		} else {
			ret = -EINVAL;
			goto out;
		}

		if (duplex == DUPLEX_FULL) {
			bmcr |= BMCR_FULLDPLX;
			if (speed != SPEED_1000)
				speed_duplex++;
		}
	} else {
		if (speed == SPEED_10) {
			if (duplex == DUPLEX_FULL) {
				anar |= ADVERTISE_10HALF | ADVERTISE_10FULL;
				speed_duplex = NWAY_10M_FULL;
			} else {
				anar |= ADVERTISE_10HALF;
				speed_duplex = NWAY_10M_HALF;
			}
		} else if (speed == SPEED_100) {
			if (duplex == DUPLEX_FULL) {
				anar |= ADVERTISE_10HALF | ADVERTISE_10FULL;
				anar |= ADVERTISE_100HALF | ADVERTISE_100FULL;
				speed_duplex = NWAY_100M_FULL;
			} else {
				anar |= ADVERTISE_10HALF;
				anar |= ADVERTISE_100HALF;
				speed_duplex = NWAY_100M_HALF;
			}
		} else if (speed == SPEED_1000 && tp->mii.supports_gmii) {
			if (duplex == DUPLEX_FULL) {
				anar |= ADVERTISE_10HALF | ADVERTISE_10FULL;
				anar |= ADVERTISE_100HALF | ADVERTISE_100FULL;
				gbcr |= ADVERTISE_1000FULL | ADVERTISE_1000HALF;
			} else {
				anar |= ADVERTISE_10HALF;
				anar |= ADVERTISE_100HALF;
				gbcr |= ADVERTISE_1000HALF;
			}
			speed_duplex = NWAY_1000M_FULL;
		} else {
			ret = -EINVAL;
			goto out;
		}

		bmcr = BMCR_ANENABLE | BMCR_ANRESTART;
	}

	if (test_and_clear_bit(PHY_RESET, &tp->flags))
		bmcr |= BMCR_RESET;

	if (tp->mii.supports_gmii)
		r8152_mdio_write(tp, MII_CTRL1000, gbcr);

	r8152_mdio_write(tp, MII_ADVERTISE, anar);
	r8152_mdio_write(tp, MII_BMCR, bmcr);

	switch (tp->version) {
	case RTL_VER_08:
	case RTL_VER_09:
		r8153b_ups_flags_w1w0(tp, ups_flags_speed(speed_duplex),
				      UPS_FLAGS_SPEED_MASK);
		break;

	default:
		break;
	}

	if (bmcr & BMCR_RESET) {
		int i;

		for (i = 0; i < 50; i++) {
			msleep(20);
			if ((r8152_mdio_read(tp, MII_BMCR) & BMCR_RESET) == 0)
				break;
		}
	}

out:
	return ret;
}