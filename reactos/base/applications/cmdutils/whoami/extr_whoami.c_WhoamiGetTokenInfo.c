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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  TOKEN_INFORMATION_CLASS ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetTokenInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TOKEN_READ ; 
 int /*<<< orphan*/  WhoamiFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  wprintf (char*,...) ; 

VOID* WhoamiGetTokenInfo(TOKEN_INFORMATION_CLASS TokenType)
{
    HANDLE hToken = 0;
    DWORD dwLength = 0;
    VOID* pTokenInfo = 0;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_READ, &hToken))
    {
        GetTokenInformation(hToken,
                            TokenType,
                            NULL,
                            dwLength,
                            &dwLength);

        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
            pTokenInfo = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwLength);
            if (pTokenInfo == NULL)
            {
                wprintf(L"ERROR: not enough memory to allocate the token structure.\r\n");
                exit(1);
            }
        }

        if (!GetTokenInformation(hToken, TokenType,
                                 (LPVOID)pTokenInfo,
                                 dwLength,
                                 &dwLength))
        {
            wprintf(L"ERROR 0x%x: could not get token information.\r\n", GetLastError());
            WhoamiFree(pTokenInfo);
            exit(1);
        }

        CloseHandle(hToken);
    }

    return pTokenInfo;
}