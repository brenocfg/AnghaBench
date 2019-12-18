#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
typedef  int WCHAR ;
struct TYPE_4__ {int Length; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int SIZE_T ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int*) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  RtlDosPathNameToNtPathName_U (int const*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlFreeUnicodeString (TYPE_1__*) ; 
 scalar_t__ SERVICE_BOOT_START ; 
 scalar_t__ ScmConvertToBootPathName (int*,int**) ; 
 int /*<<< orphan*/  _wcsnicmp (char*,int const*,int) ; 
 int /*<<< orphan*/  wcscat (int*,int const*) ; 
 int /*<<< orphan*/  wcscpy (int*,...) ; 
 int wcslen (int const*) ; 
 int /*<<< orphan*/  wcsncpy (int*,int /*<<< orphan*/ ,int) ; 

DWORD
ScmCanonDriverImagePath(DWORD dwStartType,
                        const wchar_t *lpServiceName,
                        wchar_t **lpCanonName)
{
    DWORD Result;
    SIZE_T ServiceNameLen;
    UNICODE_STRING NtServiceName;
    WCHAR *RelativeName;
    const WCHAR *SourceName = lpServiceName;

    /* Calculate the length of the service's name */
    ServiceNameLen = wcslen(lpServiceName);

    /* 12 is wcslen(L"\\SystemRoot\\") */
    if (ServiceNameLen > 12 &&
        !_wcsnicmp(L"\\SystemRoot\\", lpServiceName, 12))
    {
        /* SystemRoot prefix is already included */
        *lpCanonName = HeapAlloc(GetProcessHeap(),
                                 HEAP_ZERO_MEMORY,
                                 (ServiceNameLen + 1) * sizeof(WCHAR));

        if (*lpCanonName == NULL)
        {
            DPRINT("Error allocating memory for canonized service name!\n");
            return ERROR_NOT_ENOUGH_MEMORY;
        }

        /* If it's a boot-time driver, it must be systemroot relative */
        if (dwStartType == SERVICE_BOOT_START)
            SourceName += 12;

        /* Copy it */
        wcscpy(*lpCanonName, SourceName);

        DPRINT("Canonicalized name %S\n", *lpCanonName);
        return NO_ERROR;
    }

    /* Check if it has %SystemRoot% (len=13) */
    if (ServiceNameLen > 13 &&
        !_wcsnicmp(L"%SystemRoot%\\", lpServiceName, 13))
    {
        /* Substitute %SystemRoot% with \\SystemRoot\\ */
        *lpCanonName = HeapAlloc(GetProcessHeap(),
                                 HEAP_ZERO_MEMORY,
                                 (ServiceNameLen + 1) * sizeof(WCHAR));

        if (*lpCanonName == NULL)
        {
            DPRINT("Error allocating memory for canonized service name!\n");
            return ERROR_NOT_ENOUGH_MEMORY;
        }

        /* If it's a boot-time driver, it must be systemroot relative */
        if (dwStartType == SERVICE_BOOT_START)
            wcscpy(*lpCanonName, L"\\SystemRoot\\");

        wcscat(*lpCanonName, lpServiceName + 13);

        DPRINT("Canonicalized name %S\n", *lpCanonName);
        return NO_ERROR;
    }

    /* Check if it's a relative path name */
    if (lpServiceName[0] != L'\\' && lpServiceName[1] != L':')
    {
        *lpCanonName = HeapAlloc(GetProcessHeap(),
                                 HEAP_ZERO_MEMORY,
                                 (ServiceNameLen + 1) * sizeof(WCHAR));

        if (*lpCanonName == NULL)
        {
            DPRINT("Error allocating memory for canonized service name!\n");
            return ERROR_NOT_ENOUGH_MEMORY;
        }

        /* Just copy it over without changing */
        wcscpy(*lpCanonName, lpServiceName);

        return NO_ERROR;
    }

    /* It seems to be a DOS path, convert it */
    if (!RtlDosPathNameToNtPathName_U(lpServiceName, &NtServiceName, NULL, NULL))
    {
        DPRINT("RtlDosPathNameToNtPathName_U() failed!\n");
        return ERROR_INVALID_PARAMETER;
    }

    *lpCanonName = HeapAlloc(GetProcessHeap(),
                             HEAP_ZERO_MEMORY,
                             NtServiceName.Length + sizeof(WCHAR));

    if (*lpCanonName == NULL)
    {
        DPRINT("Error allocating memory for canonized service name!\n");
        RtlFreeUnicodeString(&NtServiceName);
        return ERROR_NOT_ENOUGH_MEMORY;
    }

    /* Copy the string */
    wcsncpy(*lpCanonName, NtServiceName.Buffer, NtServiceName.Length / sizeof(WCHAR));

    /* The unicode string is not needed anymore */
    RtlFreeUnicodeString(&NtServiceName);

    if (dwStartType != SERVICE_BOOT_START)
    {
        DPRINT("Canonicalized name %S\n", *lpCanonName);
        return NO_ERROR;
    }

    /* The service is boot-started, so must be relative */
    Result = ScmConvertToBootPathName(*lpCanonName, &RelativeName);
    if (Result)
    {
        /* There is a problem, free name and return */
        HeapFree(GetProcessHeap(), 0, *lpCanonName);
        DPRINT("Error converting named!\n");
        return Result;
    }

    ASSERT(RelativeName);

    /* Copy that string */
    wcscpy(*lpCanonName, RelativeName + 12);

    /* Free the allocated buffer */
    HeapFree(GetProcessHeap(), 0, RelativeName);

    DPRINT("Canonicalized name %S\n", *lpCanonName);

    /* Success */
    return NO_ERROR;
}