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
typedef  char* ULONG ;
typedef  int /*<<< orphan*/ * PSECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_BINARY ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  SampCreateAliasSD (int /*<<< orphan*/ **,char**) ; 
 int /*<<< orphan*/  SampRegCloseKey (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SampRegCreateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SampRegDeleteKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SampRegOpenKey (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SampRegSetValue (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int wcslen (char*) ; 

__attribute__((used)) static
NTSTATUS
SampSetupCreateAliasAccount(HANDLE hDomainKey,
                            LPCWSTR lpAccountName,
                            LPCWSTR lpDescription,
                            ULONG ulRelativeId)
{
    WCHAR szAccountKeyName[32];
    HANDLE hAccountKey = NULL;
    HANDLE hNamesKey = NULL;
    PSECURITY_DESCRIPTOR Sd = NULL;
    ULONG SdSize = 0;
    NTSTATUS Status;

    swprintf(szAccountKeyName, L"Aliases\\%08lX", ulRelativeId);

    Status = SampRegCreateKey(hDomainKey,
                              szAccountKeyName,
                              KEY_ALL_ACCESS,
                              &hAccountKey);
    if (!NT_SUCCESS(Status))
        return Status;

    Status = SampRegSetValue(hAccountKey,
                             L"Name",
                             REG_SZ,
                             (LPVOID)lpAccountName,
                             (wcslen(lpAccountName) + 1) * sizeof(WCHAR));
    if (!NT_SUCCESS(Status))
        goto done;

    Status = SampRegSetValue(hAccountKey,
                             L"Description",
                             REG_SZ,
                             (LPVOID)lpDescription,
                             (wcslen(lpDescription) + 1) * sizeof(WCHAR));
    if (!NT_SUCCESS(Status))
        goto done;

    /* Create the server SD */
    Status = SampCreateAliasSD(&Sd,
                               &SdSize);
    if (!NT_SUCCESS(Status))
        goto done;

    /* Set SecDesc attribute*/
    Status = SampRegSetValue(hAccountKey,
                             L"SecDesc",
                             REG_BINARY,
                             Sd,
                             SdSize);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = SampRegOpenKey(hDomainKey,
                            L"Aliases\\Names",
                            KEY_ALL_ACCESS,
                            &hNamesKey);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = SampRegSetValue(hNamesKey,
                            lpAccountName,
                            REG_DWORD,
                            (LPVOID)&ulRelativeId,
                            sizeof(ULONG));

done:
    SampRegCloseKey(&hNamesKey);

    if (Sd != NULL)
        RtlFreeHeap(RtlGetProcessHeap(), 0, Sd);

    if (hAccountKey != NULL)
    {
        SampRegCloseKey(&hAccountKey);

        if (!NT_SUCCESS(Status))
            SampRegDeleteKey(hDomainKey,
                             szAccountKeyName);
    }

    return Status;
}