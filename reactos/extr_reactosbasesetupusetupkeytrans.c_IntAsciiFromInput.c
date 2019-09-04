#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  size_t UINT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_5__ {scalar_t__ ScanCode; int Enhanced; scalar_t__ Normal; scalar_t__ Shift; scalar_t__ bCAPS; scalar_t__ NumLock; } ;
struct TYPE_4__ {scalar_t__ MakeCode; } ;
typedef  TYPE_1__* PKEYBOARD_INPUT_DATA ;
typedef  int DWORD ;

/* Variables and functions */
 int CAPSLOCK_ON ; 
 int ENHANCED_KEY ; 
 int NUMLOCK_ON ; 
 int SHIFT_PRESSED ; 
 TYPE_2__* ScanToAscii ; 

__attribute__((used)) static UCHAR
IntAsciiFromInput(PKEYBOARD_INPUT_DATA InputData, DWORD KeyState)
{
	UINT Counter = 0;
	USHORT Enhanced = 0;

	if (KeyState & ENHANCED_KEY) Enhanced = 1;

	while (ScanToAscii[Counter].ScanCode != 0) {
		if ((ScanToAscii[Counter].ScanCode == InputData->MakeCode)  &&
		    (ScanToAscii[Counter].Enhanced == Enhanced)) {
			if (ScanToAscii[Counter].NumLock) {
				if ((KeyState & NUMLOCK_ON) &&
				    !(KeyState & SHIFT_PRESSED)) {
					return ScanToAscii[Counter].NumLock;
				} else {
					return ScanToAscii[Counter].Normal;
				}
			}

			if ((KeyState & CAPSLOCK_ON) && ScanToAscii[Counter].bCAPS)
				KeyState ^= SHIFT_PRESSED;

			if (KeyState & SHIFT_PRESSED)
				return ScanToAscii[Counter].Shift;

			return ScanToAscii[Counter].Normal;
		}
		Counter++;
	}

	return 0;
}