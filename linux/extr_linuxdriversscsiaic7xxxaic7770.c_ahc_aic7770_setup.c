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
struct ahc_softc {char channel; char channel_b; int instruction_ram_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  bugs; int /*<<< orphan*/  features; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_AIC7770 ; 
 int /*<<< orphan*/  AHC_AIC7770_FE ; 
 int /*<<< orphan*/  AHC_PAGESCBS ; 
 int /*<<< orphan*/  AHC_TMODE_WIDEODD_BUG ; 

__attribute__((used)) static int
ahc_aic7770_setup(struct ahc_softc *ahc)
{
	ahc->channel = 'A';
	ahc->channel_b = 'B';
	ahc->chip = AHC_AIC7770;
	ahc->features = AHC_AIC7770_FE;
	ahc->bugs |= AHC_TMODE_WIDEODD_BUG;
	ahc->flags |= AHC_PAGESCBS;
	ahc->instruction_ram_size = 448;
	return (0);
}