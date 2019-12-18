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
typedef  int /*<<< orphan*/ * PUCHAR ;
typedef  int /*<<< orphan*/  PSOUND_BLASTER_PARAMETERS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SB_READ_DATA_PORT ; 
 int /*<<< orphan*/  SbRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WaitToWrite (int /*<<< orphan*/ ) ; 

BOOLEAN
SbReadData(
    PSOUND_BLASTER_PARAMETERS SBDevice,
    PUCHAR Data)
{
    if ( ! WaitToWrite(SBDevice) )
        return FALSE;

    *Data = SbRead(SBDevice, SB_READ_DATA_PORT);
    DPRINT("Read 0x%x from Sound Blaster card (data)\n", *Data);

    return TRUE;
}