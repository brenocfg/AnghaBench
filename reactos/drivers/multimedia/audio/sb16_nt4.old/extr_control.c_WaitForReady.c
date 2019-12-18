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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  PSOUND_BLASTER_PARAMETERS ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SB_TIMEOUT ; 
 int SbRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
WaitForReady(
    PSOUND_BLASTER_PARAMETERS SBDevice,
    UCHAR Port)
{
    ULONG timeout = SB_TIMEOUT;
    BOOL ready = FALSE;

    while ( ( ! ready ) && ( timeout > 0 ) )
    {
        if ( SbRead(SBDevice, Port) & 0x80 )
            return TRUE;

        timeout --;
    }

    return FALSE;
}