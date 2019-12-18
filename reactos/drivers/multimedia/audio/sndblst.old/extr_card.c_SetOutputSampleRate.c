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
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int SB_SET_OUTPUT_RATE ; 
 int /*<<< orphan*/  SB_WRITE_BYTE (int,int) ; 

VOID SetOutputSampleRate(ULONG BasePort, ULONG SampleRate)
{
    // This only works for DSP v4.xx ONLY - need a workaround!
    DPRINT("Setting output sample rate\n");

    // WAIT
//    if (! WaitToSend(BasePort))
//        return;

    SB_WRITE_BYTE(BasePort, SB_SET_OUTPUT_RATE);
    SB_WRITE_BYTE(BasePort, SampleRate / 256);  // high
    SB_WRITE_BYTE(BasePort, SampleRate % 256);  // low
}