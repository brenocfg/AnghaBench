#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  SID_NAME_USE ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertSidToStringSidW (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetUserNameW (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LookupAccountNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  szUserSID ; 

__attribute__((used)) static UINT set_user_sid_prop( MSIPACKAGE *package )
{
    SID_NAME_USE use;
    LPWSTR user_name;
    LPWSTR sid_str = NULL, dom = NULL;
    DWORD size, dom_size;
    PSID psid = NULL;
    UINT r = ERROR_FUNCTION_FAILED;

    size = 0;
    GetUserNameW( NULL, &size );

    user_name = msi_alloc( (size + 1) * sizeof(WCHAR) );
    if (!user_name)
        return ERROR_OUTOFMEMORY;

    if (!GetUserNameW( user_name, &size ))
        goto done;

    size = 0;
    dom_size = 0;
    LookupAccountNameW( NULL, user_name, NULL, &size, NULL, &dom_size, &use );

    psid = msi_alloc( size );
    dom = msi_alloc( dom_size*sizeof (WCHAR) );
    if (!psid || !dom)
    {
        r = ERROR_OUTOFMEMORY;
        goto done;
    }

    if (!LookupAccountNameW( NULL, user_name, psid, &size, dom, &dom_size, &use ))
        goto done;

    if (!ConvertSidToStringSidW( psid, &sid_str ))
        goto done;

    r = msi_set_property( package->db, szUserSID, sid_str, -1 );

done:
    LocalFree( sid_str );
    msi_free( dom );
    msi_free( psid );
    msi_free( user_name );

    return r;
}