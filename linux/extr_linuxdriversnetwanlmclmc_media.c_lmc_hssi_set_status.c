#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ clock_source; } ;
struct TYPE_14__ {TYPE_2__* lmc_media; scalar_t__ lmc_timing; TYPE_1__ ictl; } ;
typedef  TYPE_3__ lmc_softc_t ;
struct TYPE_15__ {scalar_t__ clock_source; } ;
typedef  TYPE_4__ lmc_ctl_t ;
struct TYPE_13__ {int /*<<< orphan*/  (* set_clock_source ) (TYPE_3__* const,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ LMC_CTL_CLOCK_SOURCE_EXT ; 
 scalar_t__ LMC_CTL_CLOCK_SOURCE_INT ; 
 int /*<<< orphan*/  lmc_set_protocol (TYPE_3__* const,TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__* const,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__* const,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__* const,scalar_t__) ; 

__attribute__((used)) static void
lmc_hssi_set_status (lmc_softc_t * const sc, lmc_ctl_t * ctl)
{
  if (ctl == NULL)
    {
      sc->lmc_media->set_clock_source (sc, sc->ictl.clock_source);
      lmc_set_protocol (sc, NULL);

      return;
    }

  /*
   * check for change in clock source
   */
  if (ctl->clock_source && !sc->ictl.clock_source)
    {
      sc->lmc_media->set_clock_source (sc, LMC_CTL_CLOCK_SOURCE_INT);
      sc->lmc_timing = LMC_CTL_CLOCK_SOURCE_INT;
    }
  else if (!ctl->clock_source && sc->ictl.clock_source)
    {
      sc->lmc_timing = LMC_CTL_CLOCK_SOURCE_EXT;
      sc->lmc_media->set_clock_source (sc, LMC_CTL_CLOCK_SOURCE_EXT);
    }

  lmc_set_protocol (sc, ctl);
}