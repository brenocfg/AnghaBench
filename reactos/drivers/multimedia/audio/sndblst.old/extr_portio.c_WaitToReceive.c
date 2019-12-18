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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SB_READY_TO_RECEIVE (int /*<<< orphan*/ ) ; 
 int SB_TIMEOUT ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN WaitToReceive(ULONG BasePort)
{
    int TimeOut;

    DPRINT("WaitToReceive ");

    // Check if it's OK to receive
    for (TimeOut = SB_TIMEOUT;
         ! SB_READY_TO_RECEIVE(BasePort) && TimeOut > 0;
         TimeOut --);

    // If a time-out occurs, we report failure
    if (! TimeOut)
    {
        DPRINT("FAILED\n");
        return FALSE;
    }

    DPRINT("SUCCEEDED\n");

    return TRUE;
}