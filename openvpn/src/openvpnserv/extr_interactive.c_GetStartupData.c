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
typedef  scalar_t__ WCHAR ;
struct TYPE_3__ {scalar_t__* directory; scalar_t__* options; scalar_t__* std_input; } ;
typedef  TYPE_1__ STARTUP_DATA ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_STARTUP_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  MsgToEventLog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PeekNamedPipeAsync (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int ReadPipeAsync (int /*<<< orphan*/ ,scalar_t__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReturnError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReturnLastError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  exit_event ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__* malloc (int) ; 
 int wcslen (scalar_t__*) ; 

__attribute__((used)) static BOOL
GetStartupData(HANDLE pipe, STARTUP_DATA *sud)
{
    size_t size, len;
    WCHAR *data = NULL;
    DWORD bytes, read;

    bytes = PeekNamedPipeAsync(pipe, 1, &exit_event);
    if (bytes == 0)
    {
        MsgToEventLog(M_SYSERR, TEXT("PeekNamedPipeAsync failed"));
        ReturnLastError(pipe, L"PeekNamedPipeAsync");
        goto err;
    }

    size = bytes / sizeof(*data);
    if (size == 0)
    {
        MsgToEventLog(M_SYSERR, TEXT("malformed startup data: 1 byte received"));
        ReturnError(pipe, ERROR_STARTUP_DATA, L"GetStartupData", 1, &exit_event);
        goto err;
    }

    data = malloc(bytes);
    if (data == NULL)
    {
        MsgToEventLog(M_SYSERR, TEXT("malloc failed"));
        ReturnLastError(pipe, L"malloc");
        goto err;
    }

    read = ReadPipeAsync(pipe, data, bytes, 1, &exit_event);
    if (bytes != read)
    {
        MsgToEventLog(M_SYSERR, TEXT("ReadPipeAsync failed"));
        ReturnLastError(pipe, L"ReadPipeAsync");
        goto err;
    }

    if (data[size - 1] != 0)
    {
        MsgToEventLog(M_ERR, TEXT("Startup data is not NULL terminated"));
        ReturnError(pipe, ERROR_STARTUP_DATA, L"GetStartupData", 1, &exit_event);
        goto err;
    }

    sud->directory = data;
    len = wcslen(sud->directory) + 1;
    size -= len;
    if (size <= 0)
    {
        MsgToEventLog(M_ERR, TEXT("Startup data ends at working directory"));
        ReturnError(pipe, ERROR_STARTUP_DATA, L"GetStartupData", 1, &exit_event);
        goto err;
    }

    sud->options = sud->directory + len;
    len = wcslen(sud->options) + 1;
    size -= len;
    if (size <= 0)
    {
        MsgToEventLog(M_ERR, TEXT("Startup data ends at command line options"));
        ReturnError(pipe, ERROR_STARTUP_DATA, L"GetStartupData", 1, &exit_event);
        goto err;
    }

    sud->std_input = sud->options + len;
    return TRUE;

err:
    sud->directory = NULL;              /* caller must not free() */
    free(data);
    return FALSE;
}