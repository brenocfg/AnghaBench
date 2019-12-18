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
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  char* LPCWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARRAYSIZE (char const*) ; 
 int TRUE ; 
 int /*<<< orphan*/ * heap_strdupW (char*) ; 
 char* strchrW (char*,char) ; 
 int /*<<< orphan*/  strip_spaces (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmpiW (char*,char const*,size_t) ; 

__attribute__((used)) static inline BOOL is_basic_auth_value( LPCWSTR pszAuthValue, LPWSTR *pszRealm )
{
    static const WCHAR szBasic[] = {'B','a','s','i','c'}; /* Note: not nul-terminated */
    static const WCHAR szRealm[] = {'r','e','a','l','m'}; /* Note: not nul-terminated */
    BOOL is_basic;
    is_basic = !strncmpiW(pszAuthValue, szBasic, ARRAYSIZE(szBasic)) &&
        ((pszAuthValue[ARRAYSIZE(szBasic)] == ' ') || !pszAuthValue[ARRAYSIZE(szBasic)]);
    if (is_basic && pszRealm)
    {
        LPCWSTR token;
        LPCWSTR ptr = &pszAuthValue[ARRAYSIZE(szBasic)];
        LPCWSTR realm;
        ptr++;
        *pszRealm=NULL;
        token = strchrW(ptr,'=');
        if (!token)
            return TRUE;
        realm = ptr;
        while (*realm == ' ')
            realm++;
        if(!strncmpiW(realm, szRealm, ARRAYSIZE(szRealm)) &&
            (realm[ARRAYSIZE(szRealm)] == ' ' || realm[ARRAYSIZE(szRealm)] == '='))
        {
            token++;
            while (*token == ' ')
                token++;
            if (*token == '\0')
                return TRUE;
            *pszRealm = heap_strdupW(token);
            strip_spaces(*pszRealm);
        }
    }

    return is_basic;
}