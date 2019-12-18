#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  parms ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ PhChannelParms_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * PhAttach (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Ph_DYNAMIC_BUFFER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  is_photon_available ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void qnx_init()
{
#if defined(FEAT_GUI_PHOTON)
    PhChannelParms_t parms;

    memset(&parms, 0, sizeof(parms));
    parms.flags = Ph_DYNAMIC_BUFFER;

    is_photon_available = (PhAttach(NULL, &parms) != NULL) ? TRUE : FALSE;
#endif
}