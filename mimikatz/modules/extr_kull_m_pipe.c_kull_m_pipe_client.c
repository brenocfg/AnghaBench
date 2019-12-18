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
typedef  scalar_t__* PHANDLE ;
typedef  int /*<<< orphan*/  LPCWCHAR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CreateFile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  NMPWAIT_USE_DEFAULT_WAIT ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int PIPE_READMODE_MESSAGE ; 
 int PIPE_WAIT ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  SetNamedPipeHandleState (scalar_t__,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ WaitNamedPipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL kull_m_pipe_client(LPCWCHAR pipeName, PHANDLE phPipe)
{
	BOOL status = FALSE;
	DWORD dwMode = PIPE_READMODE_MESSAGE | PIPE_WAIT;
	if(WaitNamedPipe(pipeName, NMPWAIT_USE_DEFAULT_WAIT))
	{
		*phPipe = CreateFile(pipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		if(*phPipe && (*phPipe != INVALID_HANDLE_VALUE))
		{
			if(!(status = SetNamedPipeHandleState(*phPipe, &dwMode, NULL, NULL)))
				PRINT_ERROR_AUTO(L"SetNamedPipeHandleState");
		}
		else PRINT_ERROR_AUTO(L"CreateFile");
	}
	else PRINT_ERROR_AUTO(L"WaitNamedPipe");
	return status;
}