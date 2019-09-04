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

/* Variables and functions */

void qnx_init()
{
#if defined(FEAT_GUI_PHOTON)
    PhChannelParms_t parms;

    memset(&parms, 0, sizeof(parms));
    parms.flags = Ph_DYNAMIC_BUFFER;

    is_photon_available = (PhAttach(NULL, &parms) != NULL) ? TRUE : FALSE;
#endif
}