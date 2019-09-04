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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_SHM_SHARED ; 
 int /*<<< orphan*/  B43_SHM_SH_ACKCTSPHYCTL ; 
 int /*<<< orphan*/  B43_SHM_SH_PRPHYCTL ; 
 int B43_TXH_PHY_ANT ; 
 int b43_antenna_to_phyctl (int) ; 
 int b43_shm_read16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_shm_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_mgmtframe_txantenna(struct b43_wldev *dev, int antenna)
{
	u16 ant;
	u16 tmp;

	ant = b43_antenna_to_phyctl(antenna);

	/* For ACK/CTS */
	tmp = b43_shm_read16(dev, B43_SHM_SHARED, B43_SHM_SH_ACKCTSPHYCTL);
	tmp = (tmp & ~B43_TXH_PHY_ANT) | ant;
	b43_shm_write16(dev, B43_SHM_SHARED, B43_SHM_SH_ACKCTSPHYCTL, tmp);
	/* For Probe Resposes */
	tmp = b43_shm_read16(dev, B43_SHM_SHARED, B43_SHM_SH_PRPHYCTL);
	tmp = (tmp & ~B43_TXH_PHY_ANT) | ant;
	b43_shm_write16(dev, B43_SHM_SHARED, B43_SHM_SH_PRPHYCTL, tmp);
}