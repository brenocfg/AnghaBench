#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szPropertyName ;
typedef  char WCHAR ;
struct TYPE_11__ {char* szAppName; char const* szClassName; struct TYPE_11__* next; struct TYPE_11__* overrides; } ;
struct TYPE_10__ {TYPE_2__* classes; } ;
typedef  int /*<<< orphan*/  PUXINI_FILE ;
typedef  int /*<<< orphan*/  PTHEME_PARTSTATE ;
typedef  TYPE_1__* PTHEME_FILE ;
typedef  TYPE_2__* PTHEME_CLASS ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CSTR_EQUAL ; 
 scalar_t__ CompareStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int MAX_THEME_APP_NAME ; 
 int MAX_THEME_CLASS_NAME ; 
 int MAX_THEME_VALUE_NAME ; 
 TYPE_2__* MSSTYLES_AddClass (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  MSSTYLES_AddMetric (TYPE_1__*,int,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MSSTYLES_AddPartState (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  MSSTYLES_AddProperty (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 void* MSSTYLES_FindClass (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  MSSTYLES_GetActiveThemeIni (TYPE_1__*) ; 
 scalar_t__ MSSTYLES_LookupProperty (char*,int*,int*) ; 
 scalar_t__ MSSTYLES_ParseIniSectionName (int /*<<< orphan*/ ,scalar_t__,char*,char*,int*,int*) ; 
 int /*<<< orphan*/  NORM_IGNORECASE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UXINI_CloseINI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UXINI_GetNextSection (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  UXINI_GetNextValue (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  lstrcmpiW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpynW (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (scalar_t__,int) ; 

void MSSTYLES_ParseThemeIni(PTHEME_FILE tf)
{
    static const WCHAR szSysMetrics[] = {'S','y','s','M','e','t','r','i','c','s','\0'};
    static const WCHAR szGlobals[] = {'g','l','o','b','a','l','s','\0'};
    PTHEME_CLASS cls;
    PTHEME_CLASS globals;
    PTHEME_PARTSTATE ps;
    PUXINI_FILE ini;
    WCHAR szAppName[MAX_THEME_APP_NAME];
    WCHAR szClassName[MAX_THEME_CLASS_NAME];
    WCHAR szPropertyName[MAX_THEME_VALUE_NAME];
    int iPartId;
    int iStateId;
    int iPropertyPrimitive;
    int iPropertyId;
    DWORD dwLen;
    LPCWSTR lpName;
    DWORD dwValueLen;
    LPCWSTR lpValue;

    if(tf->classes)
        return;

    ini = MSSTYLES_GetActiveThemeIni(tf);

    while((lpName=UXINI_GetNextSection(ini, &dwLen))) 
    {
        if(CompareStringW(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, lpName, dwLen, szSysMetrics, -1) == CSTR_EQUAL) 
        {
            while((lpName=UXINI_GetNextValue(ini, &dwLen, &lpValue, &dwValueLen))) 
            {
                lstrcpynW(szPropertyName, lpName, min(dwLen+1, sizeof(szPropertyName)/sizeof(szPropertyName[0])));
                if(MSSTYLES_LookupProperty(szPropertyName, &iPropertyPrimitive, &iPropertyId)) 
                {
                   /* Catch all metrics, including colors */
                   MSSTYLES_AddMetric(tf, iPropertyPrimitive, iPropertyId, lpValue, dwValueLen);
                }
                else 
                {
                    TRACE("Unknown system metric %s\n", debugstr_w(szPropertyName));
                }
            }
            continue;
        }

        if(MSSTYLES_ParseIniSectionName(lpName, dwLen, szAppName, szClassName, &iPartId, &iStateId)) 
        {
            BOOL isGlobal = FALSE;
            if(!lstrcmpiW(szClassName, szGlobals)) 
            {
                isGlobal = TRUE;
            }
            cls = MSSTYLES_AddClass(tf, szAppName, szClassName);
            ps = MSSTYLES_AddPartState(cls, iPartId, iStateId);

            while((lpName=UXINI_GetNextValue(ini, &dwLen, &lpValue, &dwValueLen))) 
            {
                lstrcpynW(szPropertyName, lpName, min(dwLen+1, sizeof(szPropertyName)/sizeof(szPropertyName[0])));
                if(MSSTYLES_LookupProperty(szPropertyName, &iPropertyPrimitive, &iPropertyId)) 
                {
                    MSSTYLES_AddProperty(ps, iPropertyPrimitive, iPropertyId, lpValue, dwValueLen, isGlobal);
                }
                else 
                {
                    TRACE("Unknown property %s\n", debugstr_w(szPropertyName));
                }
            }
        }
    }

    /* App/Class combos override values defined by the base class, map these overrides */
    globals = MSSTYLES_FindClass(tf, NULL, szGlobals);
    cls = tf->classes;
    while(cls) 
    {
        if(*cls->szAppName) 
        {
            cls->overrides = MSSTYLES_FindClass(tf, NULL, cls->szClassName);
            if(!cls->overrides) 
            {
                TRACE("No overrides found for app %s class %s\n", debugstr_w(cls->szAppName), debugstr_w(cls->szClassName));
            }
            else 
            {
                cls->overrides = globals;
            }
        }
        else 
        {
            /* Everything overrides globals..except globals */
            if(cls != globals) 
                cls->overrides = globals;
        }
        cls = cls->next;
    }
    UXINI_CloseINI(ini);

    if(!tf->classes) {
        ERR("Failed to parse theme ini\n");
    }
}