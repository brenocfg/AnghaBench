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
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,scalar_t__) ; 
 int /*<<< orphan*/  SB_DISABLE_SPEAKER ; 
 int /*<<< orphan*/  SB_ENABLE_SPEAKER ; 
 int /*<<< orphan*/  SB_WRITE_BYTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID EnableSpeaker(ULONG BasePort, BOOLEAN SpeakerOn)
{
    DPRINT("Setting speaker status %d\n", SpeakerOn);

//    if (! WaitForWrite(BasePort))
//        return;

    SB_WRITE_BYTE(BasePort, SpeakerOn ? SB_ENABLE_SPEAKER : SB_DISABLE_SPEAKER);
}