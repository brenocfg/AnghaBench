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
typedef  int /*<<< orphan*/  libbochs_t ;

/* Variables and functions */

bool bochs_cmd_stop(libbochs_t * b) {
#if __WINDOWS__
	HMODULE hKernel;
	unsigned int ExitCode;
	DWORD apiOffset = 0;
	char buffer[] = {
		0x68, 0x00, 0x00, 0x00, 0x00,	//push    0
		0x68, 0x00, 0x00, 0x00, 0x00,	//push    0
		0xE8, 0x00, 0x00, 0x00, 0x00,	//call    $
		0x83, 0x04, 0x24, 0x0A,		//add     [esp], 0A
		0x68, 0x30, 0x30, 0x30, 0x30,	//push    GenerateConsoleCtrlEvent
		0xC3,                           //retn
		0xC2, 0x04, 0x00,		//retn 4
		0xeb, 0xfe			//jmp $
	};
	hKernel = GetModuleHandle (TEXT ("kernel32"));
	apiOffset = (DWORD)GetProcAddress (hKernel, "GenerateConsoleCtrlEvent");
	*((DWORD *)&buffer[20]) = apiOffset;
	ExitCode = RunRemoteThread_(b, (const ut8*)&buffer, 0x1Eu, 0, &ExitCode) && ExitCode;
	return ExitCode;
#else
	return 0;
#endif
}