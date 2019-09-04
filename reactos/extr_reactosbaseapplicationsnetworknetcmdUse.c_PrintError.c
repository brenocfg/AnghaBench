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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  char* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 scalar_t__ FormatMessage (int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintMessageStringV (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static
VOID
PrintError(DWORD Status)
{
    WCHAR szStatusBuffer[16];
    LPWSTR Buffer;

    swprintf(szStatusBuffer, L"%lu", Status);
    PrintMessageStringV(3502, szStatusBuffer);

    if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, Status, 0, (LPWSTR)&Buffer, 0, NULL))
    {
        ConPrintf(StdErr, L"\n%s", Buffer);
        LocalFree(Buffer);
    }
}