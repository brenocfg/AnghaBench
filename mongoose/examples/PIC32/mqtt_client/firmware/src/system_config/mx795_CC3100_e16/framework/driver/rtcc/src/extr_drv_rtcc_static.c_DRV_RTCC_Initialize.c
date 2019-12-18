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
 int /*<<< orphan*/  DEVCON_ID_0 ; 
 int /*<<< orphan*/  PLIB_DEVCON_SystemUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_RTCC_AlarmDateSet (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLIB_RTCC_AlarmDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_RTCC_AlarmMaskModeSelect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PLIB_RTCC_AlarmSyncStatusGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_RTCC_AlarmTimeSet (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PLIB_RTCC_ClockRunningStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_RTCC_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_RTCC_RTCDateSet (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLIB_RTCC_RTCTimeSet (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLIB_RTCC_WriteEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTCC_ALARM_EVERY_SECOND ; 
 int /*<<< orphan*/  RTCC_ID_0 ; 

void DRV_RTCC_Initialize(void) {
  PLIB_DEVCON_SystemUnlock(DEVCON_ID_0); /* Unlock System */

  /* Initialize RTCC */
  PLIB_RTCC_WriteEnable(RTCC_ID_0); /* Enable writes to RTCC */
  PLIB_RTCC_Disable(RTCC_ID_0);     /* Disable clock to RTCC */
  while (PLIB_RTCC_ClockRunningStatus(RTCC_ID_0))
    ;                                          /*Check if clock is disabled */
  PLIB_RTCC_RTCTimeSet(RTCC_ID_0, 0x23595900); /* Set RTCC time */
  PLIB_RTCC_RTCDateSet(RTCC_ID_0, 0x14010100); /* Set RTCC date */
  PLIB_RTCC_AlarmDisable(RTCC_ID_0);           /* Disable alarm */
  while (PLIB_RTCC_AlarmSyncStatusGet(RTCC_ID_0))
    ;                                            /* Wait for disable */
  PLIB_RTCC_AlarmTimeSet(RTCC_ID_0, 0x00000500); /* Set RTCC alarm time */
  PLIB_RTCC_AlarmDateSet(RTCC_ID_0, 0x00010100); /* Set RTCC alarm date */
  PLIB_RTCC_AlarmMaskModeSelect(
      RTCC_ID_0, RTCC_ALARM_EVERY_SECOND); /* Set RTCC alarm mode */
}