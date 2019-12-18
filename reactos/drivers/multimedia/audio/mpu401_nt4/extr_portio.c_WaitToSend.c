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
 int /*<<< orphan*/  DbgPrint (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MPU401_READY_TO_SEND (int /*<<< orphan*/ ) ; 
 int MPU401_TIMEOUT ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN WaitToSend(ULONG BasePort)
{
    int TimeOut;

    DbgPrint("WaitToSend ");

    // Check if it's OK to send
    for (TimeOut = MPU401_TIMEOUT;
         ! MPU401_READY_TO_SEND(BasePort) && TimeOut > 0;
         TimeOut --);

    // If a time-out occurs, we report failure
    if (! TimeOut)
    {
        DbgPrint("FAILED\n");
        return FALSE;
    }

    DbgPrint("SUCCEEDED\n");

    return TRUE;
}