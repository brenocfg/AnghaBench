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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mdio_if_info {int (* mdio_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  prtad; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_100baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_100baseT_Half ; 
 int /*<<< orphan*/  ADVERTISED_10baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_10baseT_Half ; 
 int /*<<< orphan*/  ADVERTISED_Asym_Pause ; 
 int /*<<< orphan*/  ADVERTISED_Pause ; 
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mdio45_get_an(const struct mdio_if_info *mdio, u16 addr)
{
	u32 result = 0;
	int reg;

	reg = mdio->mdio_read(mdio->dev, mdio->prtad, MDIO_MMD_AN, addr);
	if (reg & ADVERTISE_10HALF)
		result |= ADVERTISED_10baseT_Half;
	if (reg & ADVERTISE_10FULL)
		result |= ADVERTISED_10baseT_Full;
	if (reg & ADVERTISE_100HALF)
		result |= ADVERTISED_100baseT_Half;
	if (reg & ADVERTISE_100FULL)
		result |= ADVERTISED_100baseT_Full;
	if (reg & ADVERTISE_PAUSE_CAP)
		result |= ADVERTISED_Pause;
	if (reg & ADVERTISE_PAUSE_ASYM)
		result |= ADVERTISED_Asym_Pause;
	return result;
}