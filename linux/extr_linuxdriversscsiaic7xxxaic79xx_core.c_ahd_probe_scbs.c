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
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_ASSERT_MODES (struct ahd_softc*,int,int) ; 
 int AHD_MODE_CFG_MSK ; 
 int AHD_MODE_UNKNOWN_MSK ; 
 int AHD_SCB_MAX ; 
 int /*<<< orphan*/  MK_MESSAGE ; 
 scalar_t__ SCB_BASE ; 
 scalar_t__ SCB_CONTROL ; 
 int ahd_inw_scbram (struct ahd_softc*,scalar_t__) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_outw (struct ahd_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  ahd_set_scbptr (struct ahd_softc*,int) ; 

__attribute__((used)) static int
ahd_probe_scbs(struct ahd_softc *ahd) {
	int i;

	AHD_ASSERT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
			 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
	for (i = 0; i < AHD_SCB_MAX; i++) {
		int j;

		ahd_set_scbptr(ahd, i);
		ahd_outw(ahd, SCB_BASE, i);
		for (j = 2; j < 64; j++)
			ahd_outb(ahd, SCB_BASE+j, 0);
		/* Start out life as unallocated (needing an abort) */
		ahd_outb(ahd, SCB_CONTROL, MK_MESSAGE);
		if (ahd_inw_scbram(ahd, SCB_BASE) != i)
			break;
		ahd_set_scbptr(ahd, 0);
		if (ahd_inw_scbram(ahd, SCB_BASE) != 0)
			break;
	}
	return (i);
}