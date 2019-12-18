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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ConnectNamedPipe (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_PIPE_CONNECTED ; 
 int FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 

BOOL kull_m_pipe_server_connect(HANDLE hPipe)
{
	BOOL status = FALSE;
	if(!(status = (ConnectNamedPipe(hPipe, NULL) || (GetLastError() == ERROR_PIPE_CONNECTED))))
		PRINT_ERROR_AUTO(L"ConnectNamedPipe");
	return status;
}