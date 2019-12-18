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
typedef  TYPE_1__ WINE_MCIWAVE ;
typedef  int /*<<< orphan*/  MCIDEVICEID ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mciGetDriverData (int /*<<< orphan*/ ) ; 

__attribute__((used)) static WINE_MCIWAVE *WAVE_mciGetOpenDev(MCIDEVICEID wDevID)
{
    WINE_MCIWAVE*	wmw = (WINE_MCIWAVE*)mciGetDriverData(wDevID);

    if (wmw == NULL || wmw->nUseCount == 0) {
	WARN("Invalid wDevID=%u\n", wDevID);
	return 0;
    }
    return wmw;
}