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
typedef  int uint32_t ;
typedef  int u_int ;
struct ahc_softc {int chip; int features; int /*<<< orphan*/  dev_softc; } ;

/* Variables and functions */
 int AHC_AIC7870 ; 
 int AHC_AIC7895 ; 
 int AHC_AIC7895C ; 
 int AHC_CHIPID_MASK ; 
 int AHC_ULTRA2 ; 
 int /*<<< orphan*/  DEVCONFIG ; 
 int /*<<< orphan*/  DSCOMMAND0 ; 
 int MPORTMODE ; 
 int RAMPS ; 
 int RAMPSM ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int ahc_pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ahc_ext_scbram_present(struct ahc_softc *ahc)
{
	u_int chip;
	int ramps;
	int single_user;
	uint32_t devconfig;

	chip = ahc->chip & AHC_CHIPID_MASK;
	devconfig = ahc_pci_read_config(ahc->dev_softc,
					DEVCONFIG, /*bytes*/4);
	single_user = (devconfig & MPORTMODE) != 0;

	if ((ahc->features & AHC_ULTRA2) != 0)
		ramps = (ahc_inb(ahc, DSCOMMAND0) & RAMPS) != 0;
	else if (chip == AHC_AIC7895 || chip == AHC_AIC7895C)
		/*
		 * External SCBRAM arbitration is flakey
		 * on these chips.  Unfortunately this means
		 * we don't use the extra SCB ram space on the
		 * 3940AUW.
		 */
		ramps = 0;
	else if (chip >= AHC_AIC7870)
		ramps = (devconfig & RAMPSM) != 0;
	else
		ramps = 0;

	if (ramps && single_user)
		return (1);
	return (0);
}