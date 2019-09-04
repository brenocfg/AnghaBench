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
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CSTR_EQUAL ; 
 scalar_t__ CompareStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,char*,unsigned int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 unsigned int REG_CLASS_NUMBER ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int lstrlenW (char*) ; 
 int /*<<< orphan*/ ** reg_class_keys ; 
 char** reg_class_namesW ; 

__attribute__((used)) static BOOL parseKeyName(LPWSTR lpKeyName, HKEY *hKey, LPWSTR *lpKeyPath)
{
    WCHAR* lpSlash = NULL;
    unsigned int i, len;

    if (lpKeyName == NULL)
        return FALSE;

    for(i = 0; *(lpKeyName+i) != 0; i++)
    {
        if(*(lpKeyName+i) == '\\')
        {
            lpSlash = lpKeyName+i;
            break;
        }
    }

    if (lpSlash)
    {
        len = lpSlash-lpKeyName;
    }
    else
    {
        len = lstrlenW(lpKeyName);
        lpSlash = lpKeyName+len;
    }
    *hKey = NULL;

    for (i = 0; i < REG_CLASS_NUMBER; i++) {
        if (CompareStringW(LOCALE_USER_DEFAULT, 0, lpKeyName, len, reg_class_namesW[i], len) == CSTR_EQUAL &&
            len == lstrlenW(reg_class_namesW[i])) {
            *hKey = reg_class_keys[i];
            break;
        }
    }

    if (*hKey == NULL)
        return FALSE;


    if (*lpSlash != '\0')
        lpSlash++;
    *lpKeyPath = lpSlash;
    return TRUE;
}