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
struct TYPE_2__ {int /*<<< orphan*/  dmamap; } ;
struct ahd_softc {TYPE_1__ shared_data_map; int /*<<< orphan*/  shared_data_dmat; } ;
struct ahd_completion {int dummy; } ;

/* Variables and functions */
 int AHD_SCB_MAX ; 
 int /*<<< orphan*/  ahd_dmamap_sync (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
ahd_sync_qoutfifo(struct ahd_softc *ahd, int op)
{
	ahd_dmamap_sync(ahd, ahd->shared_data_dmat, ahd->shared_data_map.dmamap,
			/*offset*/0,
			/*len*/AHD_SCB_MAX * sizeof(struct ahd_completion), op);
}