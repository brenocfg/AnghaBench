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
typedef  int UCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int MPU401_READ_DATA (scalar_t__) ; 
 scalar_t__ MPU401_TIMEOUT ; 
 int /*<<< orphan*/  MPU401_WRITE_COMMAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WaitToReceive (scalar_t__) ; 
 int /*<<< orphan*/  WaitToSend (scalar_t__) ; 

BOOLEAN InitUARTMode(ULONG BasePort)
{
    ULONG TimeOut;
    UCHAR Status = 0;

    DbgPrint("InitUARTMode() called\n");

    // Check if it's OK to send
    if (! WaitToSend(BasePort))
        return FALSE;

    DbgPrint("Resetting MPU401\n");

    // Send an MPU reset:
    MPU401_WRITE_COMMAND(BasePort, 0xff);

    // Check if it's OK to receive (some cards will ignore the above reset
    // command and so will not issue an ACK, so time out is NOT an error)
    DbgPrint("Waiting for an ACK\n");
    if (WaitToReceive(BasePort))
    {
        // Check to make sure the reset was acknowledged:
        for (TimeOut = MPU401_TIMEOUT;
             (Status = (MPU401_READ_DATA(BasePort) & 0xfe) && TimeOut > 0);
             TimeOut --);
    }

    DbgPrint("Entering UART mode\n");
    // Now we kick the MPU401 into UART ("dumb") mode
    MPU401_WRITE_COMMAND(BasePort, 0x3f);

    return TRUE;
}