#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nUseCount; } ;
typedef  TYPE_1__ WINE_MCIMIDI ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MCIDEVICEID ;

/* Variables and functions */
 scalar_t__ MCI_OPEN_DRIVER ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mciGetDriverData (int /*<<< orphan*/ ) ; 

__attribute__((used)) static WINE_MCIMIDI*  MIDI_mciGetOpenDev(MCIDEVICEID wDevID, UINT wMsg)
{
    WINE_MCIMIDI*	wmm = (WINE_MCIMIDI*)mciGetDriverData(wDevID);

    if (wmm == NULL || ((wmm->nUseCount == 0) ^ (wMsg == MCI_OPEN_DRIVER))) {
	WARN("Invalid wDevID=%u\n", wDevID);
	return 0;
    }
    return wmm;
}