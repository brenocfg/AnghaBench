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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  DisconnectNamedPipe (scalar_t__) ; 
 scalar_t__ ERROR_PIPE_NOT_CONNECTED ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetNamedPipeInfo (scalar_t__,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int PIPE_SERVER_END ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 

BOOL kull_m_pipe_close(PHANDLE phPipe)
{
	BOOL status = FALSE;
	DWORD flags = 0;
	if(*phPipe && (*phPipe != INVALID_HANDLE_VALUE))
	{
		if(GetNamedPipeInfo(*phPipe, &flags, NULL, NULL, NULL) || (GetLastError() == ERROR_PIPE_NOT_CONNECTED))
		{
			if(flags & PIPE_SERVER_END)
			{
				if(!DisconnectNamedPipe(*phPipe))
					PRINT_ERROR_AUTO(L"DisconnectNamedPipe");
			}
			if(status = CloseHandle(*phPipe))
				*phPipe = INVALID_HANDLE_VALUE;
			else PRINT_ERROR_AUTO(L"CloseHandle");
		}
		else PRINT_ERROR_AUTO(L"GetNamedPipeInfo");
	}
	return status;
}