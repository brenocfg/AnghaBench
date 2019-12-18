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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IWineMsiRemotePackage ;
typedef  int /*<<< orphan*/  IWineMsiRemoteCustomAction ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_WineMsiRemoteCustomAction ; 
 int /*<<< orphan*/  DllGetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IClassFactory_CreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  IID_IWineMsiRemoteCustomAction ; 
 int /*<<< orphan*/  IWineMsiRemoteCustomAction_GetActionInfo (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWineMsiRemoteCustomAction_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT get_action_info( const GUID *guid, INT *type, MSIHANDLE *handle,
                             BSTR *dll, BSTR *funcname,
                             IWineMsiRemotePackage **package )
{
    IClassFactory *cf = NULL;
    IWineMsiRemoteCustomAction *rca = NULL;
    HRESULT r;

    r = DllGetClassObject( &CLSID_WineMsiRemoteCustomAction,
                           &IID_IClassFactory, (LPVOID *)&cf );
    if (FAILED(r))
    {
        ERR("failed to get IClassFactory interface\n");
        return ERROR_FUNCTION_FAILED;
    }

    r = IClassFactory_CreateInstance( cf, NULL, &IID_IWineMsiRemoteCustomAction, (LPVOID *)&rca );
    if (FAILED(r))
    {
        ERR("failed to get IWineMsiRemoteCustomAction interface\n");
        return ERROR_FUNCTION_FAILED;
    }

    r = IWineMsiRemoteCustomAction_GetActionInfo( rca, guid, type, handle, dll, funcname, package );
    IWineMsiRemoteCustomAction_Release( rca );
    if (FAILED(r))
    {
        ERR("GetActionInfo failed\n");
        return ERROR_FUNCTION_FAILED;
    }

    return ERROR_SUCCESS;
}