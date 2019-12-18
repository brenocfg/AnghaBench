#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kip ;
struct TYPE_6__ {int /*<<< orphan*/  LedFlags; scalar_t__ UnitId; } ;
struct TYPE_5__ {int Flags; int MakeCode; } ;
typedef  TYPE_1__* PKEYBOARD_INPUT_DATA ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int* LPDWORD ;
typedef  TYPE_2__ KEYBOARD_INDICATOR_PARAMETERS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int CAPSLOCK_ON ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOCTL_KEYBOARD_SET_INDICATORS ; 
 int /*<<< orphan*/  KEYBOARD_CAPS_LOCK_ON ; 
 int /*<<< orphan*/  KEYBOARD_NUM_LOCK_ON ; 
 int /*<<< orphan*/  KEYBOARD_SCROLL_LOCK_ON ; 
 int KEY_BREAK ; 
 int KEY_E0 ; 
 int KEY_E1 ; 
 int LEFT_ALT_PRESSED ; 
 int LEFT_CTRL_PRESSED ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int NUMLOCK_ON ; 
 int /*<<< orphan*/  NtDeviceIoControlFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RIGHT_ALT_PRESSED ; 
 int RIGHT_CTRL_PRESSED ; 
 int SCROLLLOCK_ON ; 
 int SHIFT_PRESSED ; 

__attribute__((used)) static void
IntUpdateControlKeyState(HANDLE hConsoleInput, LPDWORD State, PKEYBOARD_INPUT_DATA InputData)
{
	DWORD Value = 0;
    DWORD oldState, newState;

	if (InputData->Flags & KEY_E1) /* Only the pause key has E1 */
		return;

    oldState = newState = *State;

	if (!(InputData->Flags & KEY_E0)) {
		switch (InputData->MakeCode) {
			case 0x2a:
			case 0x36:
				Value = SHIFT_PRESSED;
				break;

			case 0x1d:
				Value = LEFT_CTRL_PRESSED;
				break;

			case 0x38:
				Value = LEFT_ALT_PRESSED;
				break;

			case 0x3A:
				if (!(InputData->Flags & KEY_BREAK))
					newState ^= CAPSLOCK_ON;
				break;

			case 0x45:
				if (!(InputData->Flags & KEY_BREAK))
					newState ^= NUMLOCK_ON;
				break;

			case 0x46:
				if (!(InputData->Flags & KEY_BREAK))
					newState ^= SCROLLLOCK_ON;
				break;

			default:
				return;
		}
	} else {
		switch (InputData->MakeCode) {
			case 0x1d:
				Value = RIGHT_CTRL_PRESSED;
				break;

			case 0x38:
				Value = RIGHT_ALT_PRESSED;
				break;

			default:
				return;
		}
	}

    /* Check if the state of the indicators has been changed */
    if ((oldState ^ newState) & (NUMLOCK_ON | CAPSLOCK_ON | SCROLLLOCK_ON))
    {
        IO_STATUS_BLOCK               IoStatusBlock;
        NTSTATUS                      Status;
        KEYBOARD_INDICATOR_PARAMETERS kip;

        kip.LedFlags = 0;
        kip.UnitId   = 0;

        if ((newState & NUMLOCK_ON))
            kip.LedFlags |= KEYBOARD_NUM_LOCK_ON;

        if ((newState & CAPSLOCK_ON))
            kip.LedFlags |= KEYBOARD_CAPS_LOCK_ON;

        if ((newState & SCROLLLOCK_ON))
            kip.LedFlags |= KEYBOARD_SCROLL_LOCK_ON;

        /* Update the state of the leds on primary keyboard */
        DPRINT("NtDeviceIoControlFile dwLeds=%x\n", kip.LedFlags);

        Status = NtDeviceIoControlFile(
              hConsoleInput,
              NULL,
              NULL,
              NULL,
              &IoStatusBlock,
              IOCTL_KEYBOARD_SET_INDICATORS,
		      &kip,
              sizeof(kip),
		      NULL,
              0);

        if (!NT_SUCCESS(Status))
        {
            DPRINT1("NtDeviceIoControlFile(IOCTL_KEYBOARD_SET_INDICATORS) failed (Status %lx)\n", Status);
        }
    } else
    /* Normal press/release state handling */
	if (InputData->Flags & KEY_BREAK)
		newState &= ~Value;
	else
		newState |= Value;

    *State = newState;
}