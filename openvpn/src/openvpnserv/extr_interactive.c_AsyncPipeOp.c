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
typedef  scalar_t__ async_op_t ;
typedef  int /*<<< orphan*/  OVERLAPPED ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__* LPHANDLE ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CancelIo (scalar_t__) ; 
 int /*<<< orphan*/  CloseHandleEx (scalar_t__*) ; 
 scalar_t__ ERROR_IO_PENDING ; 
 scalar_t__ ERROR_MORE_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetOverlappedResult (scalar_t__,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  IO_TIMEOUT ; 
 scalar_t__ InitOverlapped (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PeekNamedPipe (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReadFile (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int WAIT_OBJECT_0 ; 
 int WaitForMultipleObjects (int,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__* malloc (int) ; 
 scalar_t__ peek ; 
 scalar_t__ write ; 

__attribute__((used)) static DWORD
AsyncPipeOp(async_op_t op, HANDLE pipe, LPVOID buffer, DWORD size, DWORD count, LPHANDLE events)
{
    DWORD i;
    BOOL success;
    HANDLE io_event;
    DWORD res, bytes = 0;
    OVERLAPPED overlapped;
    LPHANDLE handles = NULL;

    io_event = InitOverlapped(&overlapped);
    if (!io_event)
    {
        goto out;
    }

    handles = malloc((count + 1) * sizeof(HANDLE));
    if (!handles)
    {
        goto out;
    }

    if (op == write)
    {
        success = WriteFile(pipe, buffer, size, NULL, &overlapped);
    }
    else
    {
        success = ReadFile(pipe, buffer, size, NULL, &overlapped);
    }
    if (!success && GetLastError() != ERROR_IO_PENDING && GetLastError() != ERROR_MORE_DATA)
    {
        goto out;
    }

    handles[0] = io_event;
    for (i = 0; i < count; i++)
    {
        handles[i + 1] = events[i];
    }

    res = WaitForMultipleObjects(count + 1, handles, FALSE,
                                 op == peek ? INFINITE : IO_TIMEOUT);
    if (res != WAIT_OBJECT_0)
    {
        CancelIo(pipe);
        goto out;
    }

    if (op == peek)
    {
        PeekNamedPipe(pipe, NULL, 0, NULL, &bytes, NULL);
    }
    else
    {
        GetOverlappedResult(pipe, &overlapped, &bytes, TRUE);
    }

out:
    CloseHandleEx(&io_event);
    free(handles);
    return bytes;
}