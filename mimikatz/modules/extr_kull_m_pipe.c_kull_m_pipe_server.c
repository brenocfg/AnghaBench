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
typedef  int /*<<< orphan*/  LPCWCHAR ;
typedef  scalar_t__ HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ CreateNamedPipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  NMPWAIT_USE_DEFAULT_WAIT ; 
 int /*<<< orphan*/  PIPE_ACCESS_DUPLEX ; 
 int PIPE_READMODE_MESSAGE ; 
 int PIPE_TYPE_MESSAGE ; 
 int PIPE_WAIT ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 

BOOL kull_m_pipe_server(LPCWCHAR pipeName, HANDLE *phPipe)
{
	BOOL status = FALSE;
	*phPipe = CreateNamedPipe(pipeName,  PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, 1, 0, 0, NMPWAIT_USE_DEFAULT_WAIT, NULL);
	if(!(status = (*phPipe && (*phPipe != INVALID_HANDLE_VALUE))))
		PRINT_ERROR_AUTO(L"CreateNamedPipe");
	return status;
}