#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {int /*<<< orphan*/  package; } ;
struct TYPE_10__ {int len; } ;
struct TYPE_9__ {int /*<<< orphan*/  TargetPath; } ;
typedef  TYPE_1__ MSIFILE ;
typedef  TYPE_2__ FORMSTR ;
typedef  TYPE_3__ FORMAT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int GetShortPathNameW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_formstr_data (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* msi_get_loaded_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdupW (int /*<<< orphan*/ ) ; 
 int strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static WCHAR *deformat_file( FORMAT *format, FORMSTR *str, BOOL shortname, int *ret_len )
{
    WCHAR *key, *ret = NULL;
    const MSIFILE *file;
    DWORD len = 0;

    if (!(key = msi_alloc( (str->len + 1) * sizeof(WCHAR) ))) return NULL;
    lstrcpynW(key, get_formstr_data(format, str), str->len + 1);

    if (!(file = msi_get_loaded_file( format->package, key ))) goto done;
    if (!shortname)
    {
        if ((ret = strdupW( file->TargetPath ))) len = strlenW( ret );
        goto done;
    }
    if ((len = GetShortPathNameW(file->TargetPath, NULL, 0)) <= 0)
    {
        if ((ret = strdupW( file->TargetPath ))) len = strlenW( ret );
        goto done;
    }
    len++;
    if ((ret = msi_alloc( len * sizeof(WCHAR) )))
        len = GetShortPathNameW( file->TargetPath, ret, len );

done:
    msi_free( key );
    *ret_len = len;
    return ret;
}