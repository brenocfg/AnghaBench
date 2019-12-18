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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  char const* LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int lstrlenW (char const*) ; 
 int /*<<< orphan*/  msi_alloc (int) ; 
 int /*<<< orphan*/  sprintfW (int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  strdupW (char const*) ; 

__attribute__((used)) static LPWSTR msi_get_deferred_action(LPCWSTR action, LPCWSTR actiondata,
                                      LPCWSTR usersid, LPCWSTR prodcode)
{
    LPWSTR deferred;
    DWORD len;

    static const WCHAR format[] = {
            '[','%','s','<','=','>','%','s','<','=','>','%','s',']','%','s',0
    };

    if (!actiondata)
        return strdupW(action);

    len = lstrlenW(action) + lstrlenW(actiondata) +
          lstrlenW(usersid) + lstrlenW(prodcode) +
          lstrlenW(format) - 7;
    deferred = msi_alloc(len * sizeof(WCHAR));

    sprintfW(deferred, format, actiondata, usersid, prodcode, action);
    return deferred;
}