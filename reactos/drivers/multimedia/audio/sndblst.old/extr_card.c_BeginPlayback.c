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
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  SB_WRITE_BYTE (int,int) ; 

VOID BeginPlayback(ULONG BasePort, ULONG BitDepth, ULONG Channels, ULONG BlockSize)
{
    DPRINT("BeginPlayback(%d, %d, %d, %d)\n", BasePort, BitDepth, Channels, BlockSize);

//    switch(BitDepth)
//    {
//        case 8 :    Command = 0xc0; break;
//        case 16 :   Command = 0xb0; break;  // Make sure we support it
//        default :   Command = 0xc0;
//    }

    DPRINT("Initiating playback\n");

    // TEMPORARY:
    SB_WRITE_BYTE(BasePort, 0xc6);
    SB_WRITE_BYTE(BasePort, 0); // mode - TEMPORARY
    SB_WRITE_BYTE(BasePort, BlockSize % 256);
    SB_WRITE_BYTE(BasePort, BlockSize / 256);
}