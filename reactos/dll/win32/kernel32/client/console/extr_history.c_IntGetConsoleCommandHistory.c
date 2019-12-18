#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int USHORT ;
struct TYPE_10__ {TYPE_2__* ProcessParameters; } ;
struct TYPE_8__ {int ExeLength; scalar_t__ HistoryLength; int /*<<< orphan*/  History; int /*<<< orphan*/  ExeName; scalar_t__ Unicode2; scalar_t__ Unicode; int /*<<< orphan*/  ConsoleHandle; } ;
struct TYPE_6__ {TYPE_3__ GetCommandHistoryRequest; } ;
struct TYPE_9__ {int /*<<< orphan*/  Status; TYPE_1__ Data; } ;
struct TYPE_7__ {int /*<<< orphan*/  ConsoleHandle; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PCSR_CAPTURE_BUFFER ;
typedef  int /*<<< orphan*/  PCSR_API_MESSAGE ;
typedef  TYPE_3__* PCONSOLE_GETCOMMANDHISTORY ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/ * LPCVOID ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_4__ CONSOLE_API_MESSAGE ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BaseSetLastNTError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONSRV_SERVERDLL_INDEX ; 
 int /*<<< orphan*/  CSR_CREATE_API_NUMBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConsolepGetCommandHistory ; 
 int /*<<< orphan*/  CsrAllocateCaptureBuffer (int,scalar_t__) ; 
 int /*<<< orphan*/  CsrAllocateMessagePointer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CsrCaptureMessageBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CsrClientCallServer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CsrFreeCaptureBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 TYPE_5__* NtCurrentPeb () ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD
IntGetConsoleCommandHistory(LPVOID lpHistory, DWORD cbHistory, LPCVOID lpExeName, BOOLEAN bUnicode)
{
    CONSOLE_API_MESSAGE ApiMessage;
    PCONSOLE_GETCOMMANDHISTORY GetCommandHistoryRequest = &ApiMessage.Data.GetCommandHistoryRequest;
    PCSR_CAPTURE_BUFFER CaptureBuffer;

    USHORT NumChars = (USHORT)(lpExeName ? (bUnicode ? wcslen(lpExeName) : strlen(lpExeName)) : 0);

    if (lpExeName == NULL || NumChars == 0)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;
    }

    GetCommandHistoryRequest->ConsoleHandle = NtCurrentPeb()->ProcessParameters->ConsoleHandle;
    GetCommandHistoryRequest->HistoryLength = cbHistory;
    GetCommandHistoryRequest->ExeLength     = NumChars * (bUnicode ? sizeof(WCHAR) : sizeof(CHAR));
    GetCommandHistoryRequest->Unicode  =
    GetCommandHistoryRequest->Unicode2 = bUnicode;

    // CaptureBuffer = CsrAllocateCaptureBuffer(2, IntStringSize(lpExeName, bUnicode) +
    //                                             HistoryLength);
    CaptureBuffer = CsrAllocateCaptureBuffer(2, GetCommandHistoryRequest->ExeLength +
                                                GetCommandHistoryRequest->HistoryLength);
    if (!CaptureBuffer)
    {
        DPRINT1("CsrAllocateCaptureBuffer failed!\n");
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return 0;
    }

    CsrCaptureMessageBuffer(CaptureBuffer,
                            (PVOID)lpExeName,
                            GetCommandHistoryRequest->ExeLength,
                            (PVOID)&GetCommandHistoryRequest->ExeName);

    CsrAllocateMessagePointer(CaptureBuffer, GetCommandHistoryRequest->HistoryLength,
                              (PVOID*)&GetCommandHistoryRequest->History);

    CsrClientCallServer((PCSR_API_MESSAGE)&ApiMessage,
                        CaptureBuffer,
                        CSR_CREATE_API_NUMBER(CONSRV_SERVERDLL_INDEX, ConsolepGetCommandHistory),
                        sizeof(*GetCommandHistoryRequest));
    if (!NT_SUCCESS(ApiMessage.Status))
    {
        CsrFreeCaptureBuffer(CaptureBuffer);
        BaseSetLastNTError(ApiMessage.Status);
        return 0;
    }

    RtlCopyMemory(lpHistory,
                  GetCommandHistoryRequest->History,
                  GetCommandHistoryRequest->HistoryLength);

    CsrFreeCaptureBuffer(CaptureBuffer);

    return GetCommandHistoryRequest->HistoryLength;
}