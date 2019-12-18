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
typedef  int ULONG ;
struct TYPE_10__ {TYPE_2__* ProcessParameters; } ;
struct TYPE_8__ {int SourceLength; int ExeLength; int TargetLength; int /*<<< orphan*/ * Target; int /*<<< orphan*/  ExeName; int /*<<< orphan*/  Source; scalar_t__ Unicode2; scalar_t__ Unicode; int /*<<< orphan*/  ConsoleHandle; } ;
struct TYPE_6__ {TYPE_3__ ConsoleAliasRequest; } ;
struct TYPE_9__ {int /*<<< orphan*/  Status; TYPE_1__ Data; } ;
struct TYPE_7__ {int /*<<< orphan*/  ConsoleHandle; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/ * PCSR_CAPTURE_BUFFER ;
typedef  int /*<<< orphan*/  PCSR_API_MESSAGE ;
typedef  TYPE_3__* PCONSOLE_ADDGETALIAS ;
typedef  int /*<<< orphan*/ * LPCVOID ;
typedef  TYPE_4__ CONSOLE_API_MESSAGE ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BaseSetLastNTError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONSRV_SERVERDLL_INDEX ; 
 int /*<<< orphan*/  CSR_CREATE_API_NUMBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConsolepAddAlias ; 
 int /*<<< orphan*/ * CsrAllocateCaptureBuffer (int,int) ; 
 int /*<<< orphan*/  CsrCaptureMessageBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CsrClientCallServer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CsrFreeCaptureBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 TYPE_5__* NtCurrentPeb () ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
IntAddConsoleAlias(LPCVOID Source,
                   USHORT SourceBufferLength,
                   LPCVOID Target,
                   USHORT TargetBufferLength,
                   LPCVOID lpExeName,
                   BOOLEAN bUnicode)
{
    CONSOLE_API_MESSAGE ApiMessage;
    PCONSOLE_ADDGETALIAS ConsoleAliasRequest = &ApiMessage.Data.ConsoleAliasRequest;
    PCSR_CAPTURE_BUFFER CaptureBuffer;
    ULONG CapturedStrings;

    USHORT NumChars = (USHORT)(lpExeName ? (bUnicode ? wcslen(lpExeName) : strlen(lpExeName)) : 0);

    if (lpExeName == NULL || NumChars == 0)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    ConsoleAliasRequest->ConsoleHandle = NtCurrentPeb()->ProcessParameters->ConsoleHandle;

    /* Determine the needed sizes */
    ConsoleAliasRequest->SourceLength = SourceBufferLength;
    ConsoleAliasRequest->ExeLength    = NumChars * (bUnicode ? sizeof(WCHAR) : sizeof(CHAR));
    ConsoleAliasRequest->Unicode  =
    ConsoleAliasRequest->Unicode2 = bUnicode;

    CapturedStrings = 2;

    if (Target) /* The target can be optional */
    {
        ConsoleAliasRequest->TargetLength = TargetBufferLength;
        CapturedStrings++;
    }
    else
    {
        ConsoleAliasRequest->TargetLength = 0;
    }

    /* Allocate a Capture Buffer */
    CaptureBuffer = CsrAllocateCaptureBuffer(CapturedStrings,
                                             ConsoleAliasRequest->SourceLength +
                                             ConsoleAliasRequest->ExeLength    +
                                             ConsoleAliasRequest->TargetLength);
    if (CaptureBuffer == NULL)
    {
        DPRINT1("CsrAllocateCaptureBuffer failed!\n");
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return FALSE;
    }

    /* Capture the strings */
    CsrCaptureMessageBuffer(CaptureBuffer,
                            (PVOID)Source,
                            ConsoleAliasRequest->SourceLength,
                            (PVOID*)&ConsoleAliasRequest->Source);

    CsrCaptureMessageBuffer(CaptureBuffer,
                            (PVOID)lpExeName,
                            ConsoleAliasRequest->ExeLength,
                            (PVOID*)&ConsoleAliasRequest->ExeName);

    if (Target) /* The target can be optional */
    {
        CsrCaptureMessageBuffer(CaptureBuffer,
                                (PVOID)Target,
                                ConsoleAliasRequest->TargetLength,
                                (PVOID*)&ConsoleAliasRequest->Target);
    }
    else
    {
        ConsoleAliasRequest->Target = NULL;
    }

    CsrClientCallServer((PCSR_API_MESSAGE)&ApiMessage,
                        CaptureBuffer,
                        CSR_CREATE_API_NUMBER(CONSRV_SERVERDLL_INDEX, ConsolepAddAlias),
                        sizeof(*ConsoleAliasRequest));

    CsrFreeCaptureBuffer(CaptureBuffer);

    if (!NT_SUCCESS(ApiMessage.Status))
    {
        BaseSetLastNTError(ApiMessage.Status);
        return FALSE;
    }

    return TRUE;
}