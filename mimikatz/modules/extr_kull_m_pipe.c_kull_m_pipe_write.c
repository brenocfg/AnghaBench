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
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FlushFileBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 scalar_t__ WriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 

BOOL kull_m_pipe_write(HANDLE hPipe, LPCVOID buffer, DWORD size)
{
	BOOL status = FALSE;
	DWORD nbWritten;
	if(WriteFile(hPipe, buffer, size, &nbWritten, NULL) && (size == nbWritten))
	{
		if(!(status = FlushFileBuffers(hPipe)))
			PRINT_ERROR_AUTO(L"FlushFileBuffers");
	}
	else PRINT_ERROR_AUTO(L"WriteFile");
	return status;
}