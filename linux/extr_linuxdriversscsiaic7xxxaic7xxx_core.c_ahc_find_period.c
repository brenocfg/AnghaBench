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
typedef  size_t u_int ;
struct ahc_syncrate {size_t sxfr_u2; size_t period; size_t sxfr; int /*<<< orphan*/ * rate; } ;
struct ahc_softc {int features; } ;

/* Variables and functions */
 int AHC_DT ; 
 size_t AHC_SYNCRATE_FAST ; 
 size_t AHC_SYNCRATE_ULTRA ; 
 size_t AHC_SYNCRATE_ULTRA2 ; 
 int AHC_ULTRA ; 
 int AHC_ULTRA2 ; 
 size_t SXFR ; 
 size_t SXFR_ULTRA2 ; 
 struct ahc_syncrate* ahc_syncrates ; 

u_int
ahc_find_period(struct ahc_softc *ahc, u_int scsirate, u_int maxsync)
{
	const struct ahc_syncrate *syncrate;

	if ((ahc->features & AHC_ULTRA2) != 0)
		scsirate &= SXFR_ULTRA2;
	else
		scsirate &= SXFR;

	/* now set maxsync based on card capabilities */
	if ((ahc->features & AHC_DT) == 0 && maxsync < AHC_SYNCRATE_ULTRA2)
		maxsync = AHC_SYNCRATE_ULTRA2;
	if ((ahc->features & (AHC_DT | AHC_ULTRA2)) == 0
	    && maxsync < AHC_SYNCRATE_ULTRA)
		maxsync = AHC_SYNCRATE_ULTRA;
	if ((ahc->features & (AHC_DT | AHC_ULTRA2 | AHC_ULTRA)) == 0
	    && maxsync < AHC_SYNCRATE_FAST)
		maxsync = AHC_SYNCRATE_FAST;


	syncrate = &ahc_syncrates[maxsync];
	while (syncrate->rate != NULL) {

		if ((ahc->features & AHC_ULTRA2) != 0) {
			if (syncrate->sxfr_u2 == 0)
				break;
			else if (scsirate == (syncrate->sxfr_u2 & SXFR_ULTRA2))
				return (syncrate->period);
		} else if (scsirate == (syncrate->sxfr & SXFR)) {
				return (syncrate->period);
		}
		syncrate++;
	}
	return (0); /* async */
}