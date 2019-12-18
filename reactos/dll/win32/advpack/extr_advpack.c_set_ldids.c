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
typedef  char WCHAR ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/ * HINF ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int MAX_FIELD_LENGTH ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetupFindFirstLineW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetLineTextW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char*,int,int*) ; 
 int /*<<< orphan*/  SetupGetStringFieldW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  SetupSetDirectoryIdW (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  get_dest_dir (int /*<<< orphan*/ *,char*,char*,int) ; 
 char* get_parameter (char**,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcmpiW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpynW (char*,int /*<<< orphan*/ *,int) ; 
 char* wcschr (char*,char) ; 
 int wcstol (char*,int /*<<< orphan*/ *,int) ; 

void set_ldids(HINF hInf, LPCWSTR pszInstallSection, LPCWSTR pszWorkingDir)
{
    WCHAR field[MAX_FIELD_LENGTH];
    WCHAR line[MAX_FIELD_LENGTH];
    WCHAR dest[MAX_PATH];
    INFCONTEXT context;
    DWORD size;
    int ldid;

    static const WCHAR source_dir[] = {'S','o','u','r','c','e','D','i','r',0};

    static const WCHAR custDestW[] = {
        'C','u','s','t','o','m','D','e','s','t','i','n','a','t','i','o','n',0
    };

    if (!SetupGetLineTextW(NULL, hInf, pszInstallSection, custDestW,
                           field, MAX_FIELD_LENGTH, &size))
        return;

    if (!SetupFindFirstLineW(hInf, field, NULL, &context))
        return;

    do
    {
        LPWSTR value, ptr, key, key_copy = NULL;
        DWORD flags = 0;

        SetupGetLineTextW(&context, NULL, NULL, NULL,
                          line, MAX_FIELD_LENGTH, &size);

        /* SetupGetLineTextW returns the value if there is only one key, but
         * returns the whole line if there is more than one key
         */
        if (!(value = wcschr(line, '=')))
        {
            SetupGetStringFieldW(&context, 0, NULL, 0, &size);
            key = HeapAlloc(GetProcessHeap(), 0, size * sizeof(WCHAR));
            key_copy = key;
            SetupGetStringFieldW(&context, 0, key, size, &size);
            value = line;
        }
        else
        {
            key = line;
            *(value++) = '\0';
        }

        /* remove leading whitespace from the value */
        while (*value == ' ')
            value++;

        /* Extract the flags */
        ptr = wcschr(value, ',');
        if (ptr) {
            *ptr = '\0';
            flags = wcstol(ptr+1, NULL, 10);
        }

        /* set dest to pszWorkingDir if key is SourceDir */
        if (pszWorkingDir && !lstrcmpiW(value, source_dir))
            lstrcpynW(dest, pszWorkingDir, MAX_PATH);
        else
            get_dest_dir(hInf, value, dest, MAX_PATH);

        /* If prompting required, provide dialog to request path */
        if (flags & 0x04)
            FIXME("Need to support changing paths - default will be used\n");

        /* set all ldids to dest */
        while ((ptr = get_parameter(&key, ',', FALSE)))
        {
            ldid = wcstol(ptr, NULL, 10);
            SetupSetDirectoryIdW(hInf, ldid, dest);
        }
        HeapFree(GetProcessHeap(), 0, key_copy);
    } while (SetupFindNextLine(&context, &context));
}