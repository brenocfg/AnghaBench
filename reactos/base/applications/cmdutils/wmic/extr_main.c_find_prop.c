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
typedef  int /*<<< orphan*/  SAFEARRAY ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IWbemClassObject ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ IWbemClassObject_GetNames (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SafeArrayDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SafeArrayGetElement (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SafeArrayGetUBound (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  WBEM_FLAG_ALWAYS ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * strdupW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *find_prop( IWbemClassObject *class, const WCHAR *prop )
{
    SAFEARRAY *sa;
    WCHAR *ret = NULL;
    LONG i, last_index = 0;
    BSTR str;

    if (IWbemClassObject_GetNames( class, NULL, WBEM_FLAG_ALWAYS, NULL, &sa ) != S_OK) return NULL;

    SafeArrayGetUBound( sa, 1, &last_index );
    for (i = 0; i <= last_index; i++)
    {
        SafeArrayGetElement( sa, &i, &str );
        if (!strcmpiW( str, prop ))
        {
            ret = strdupW( str );
            break;
        }
    }
    SafeArrayDestroy( sa );
    return ret;
}