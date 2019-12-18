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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int len; } ;
typedef  TYPE_1__ FORMSTR ;
typedef  int /*<<< orphan*/  FORMAT ;
typedef  int DWORD ;

/* Variables and functions */
 int GetEnvironmentVariableW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_formstr_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static WCHAR *deformat_environment( FORMAT *format, FORMSTR *str, int *ret_len )
{
    WCHAR *key, *ret = NULL;
    DWORD len;

    if (!(key = msi_alloc((str->len + 1) * sizeof(WCHAR)))) return NULL;
    lstrcpynW(key, get_formstr_data(format, str), str->len + 1);

    if ((len = GetEnvironmentVariableW( key, NULL, 0 )))
    {
        len++;
        if ((ret = msi_alloc( len * sizeof(WCHAR) )))
            *ret_len = GetEnvironmentVariableW( key, ret, len );
    }
    msi_free( key );
    return ret;
}