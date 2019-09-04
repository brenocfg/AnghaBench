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
typedef  int /*<<< orphan*/  abKeystate ;
typedef  scalar_t__ WORD ;
typedef  int UINT ;
struct TYPE_3__ {int dwControlKeyState; scalar_t__ AChar; int /*<<< orphan*/  wVirtualScanCode; int /*<<< orphan*/  wVirtualKeyCode; } ;
typedef  TYPE_1__ KEY_EVENT_RECORD ;
typedef  void* CHAR ;
typedef  int BYTE ;

/* Variables and functions */
 int ALT_GR ; 
 int CAPSLOCK_ON ; 
 int /*<<< orphan*/  KLF_ACTIVATE ; 
 int KL_NAMELENGTH ; 
 int /*<<< orphan*/  LoadKeyboardLayout (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MapVirtualKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SHIFT_PRESSED ; 
 int ToAscii (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__*,int /*<<< orphan*/ ) ; 
 size_t VK_CAPITAL ; 
 size_t VK_CONTROL ; 
 size_t VK_LCONTROL ; 
 size_t VK_MENU ; 
 size_t VK_RMENU ; 
 size_t VK_SHIFT ; 
 int /*<<< orphan*/  VK_SPACE ; 
 scalar_t__ s_pfnGetConsoleKeyboardLayoutName (void**) ; 
 scalar_t__ stub1 (void**) ; 
 int /*<<< orphan*/  vim_memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
#ifdef __BORLANDC__
    __stdcall
#endif
win32_kbd_patch_key(
    KEY_EVENT_RECORD *pker)
{
    UINT uMods = pker->dwControlKeyState;
    static int s_iIsDead = 0;
    static WORD awAnsiCode[2];
    static BYTE abKeystate[256];


    if (s_iIsDead == 2)
    {
	pker->AChar = (CHAR) awAnsiCode[1];
	s_iIsDead = 0;
	return 1;
    }

    if (pker->AChar != 0)
	return 1;

    vim_memset(abKeystate, 0, sizeof (abKeystate));

    // Should only be non-NULL on NT 4.0
    if (s_pfnGetConsoleKeyboardLayoutName != NULL)
    {
	CHAR szKLID[KL_NAMELENGTH];

	if ((*s_pfnGetConsoleKeyboardLayoutName)(szKLID))
	    (void)LoadKeyboardLayout(szKLID, KLF_ACTIVATE);
    }

    /* Clear any pending dead keys */
    ToAscii(VK_SPACE, MapVirtualKey(VK_SPACE, 0), abKeystate, awAnsiCode, 0);

    if (uMods & SHIFT_PRESSED)
	abKeystate[VK_SHIFT] = 0x80;
    if (uMods & CAPSLOCK_ON)
	abKeystate[VK_CAPITAL] = 1;

    if ((uMods & ALT_GR) == ALT_GR)
    {
	abKeystate[VK_CONTROL] = abKeystate[VK_LCONTROL] =
	    abKeystate[VK_MENU] = abKeystate[VK_RMENU] = 0x80;
    }

    s_iIsDead = ToAscii(pker->wVirtualKeyCode, pker->wVirtualScanCode,
			abKeystate, awAnsiCode, 0);

    if (s_iIsDead > 0)
	pker->AChar = (CHAR) awAnsiCode[0];

    return s_iIsDead;
}