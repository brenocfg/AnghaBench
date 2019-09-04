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
struct TYPE_3__ {int MakeCode; } ;
typedef  TYPE_1__* PKEYBOARD_INPUT_DATA ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int) ; 
 int ENHANCED_KEY ; 
 int* KeyTable ; 
 int* KeyTableEnhanced ; 
 int* KeyTableNumlock ; 
 int NUMLOCK_ON ; 

__attribute__((used)) static DWORD
IntVKFromKbdInput(PKEYBOARD_INPUT_DATA InputData, DWORD KeyState)
{
	if (!(KeyState & ENHANCED_KEY)) {
		if ((KeyState & NUMLOCK_ON) &&
		    KeyTableNumlock[InputData->MakeCode & 0x7f]) {
			DPRINT("Numlock, using %x\n",
			       InputData->MakeCode & 0x7f);
			return KeyTableNumlock[InputData->MakeCode & 0x7f];
		}
		DPRINT("Not enhanced, using %x\n", InputData->MakeCode & 0x7f);
		return KeyTable[InputData->MakeCode & 0x7f];
	}

	DPRINT("Enhanced, using %x\n", InputData->MakeCode & 0x7f);
	return KeyTableEnhanced[InputData->MakeCode & 0x7f];
}