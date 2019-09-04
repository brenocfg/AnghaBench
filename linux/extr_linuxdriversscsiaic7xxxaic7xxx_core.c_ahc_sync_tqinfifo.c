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
struct ahc_softc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
ahc_sync_tqinfifo(struct ahc_softc *ahc, int op)
{
#ifdef AHC_TARGET_MODE
	if ((ahc->flags & AHC_TARGETROLE) != 0) {
		ahc_dmamap_sync(ahc, ahc->shared_data_dmat,
				ahc->shared_data_dmamap,
				ahc_targetcmd_offset(ahc, 0),
				sizeof(struct target_cmd) * AHC_TMODE_CMDS,
				op);
	}
#endif
}