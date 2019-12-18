#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int install_type; int /*<<< orphan*/ * tmp_dir; int /*<<< orphan*/  install_file; scalar_t__ callback; } ;
typedef  TYPE_1__ install_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BINDSTATUS_INSTALLINGCOMPONENTS ; 
 scalar_t__ CreateDirectoryW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GetTempFileNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTempPathW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetTickCount () ; 
 int /*<<< orphan*/  IBindStatusCallback_OnProgress (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  INSTALL_DLL 129 
#define  INSTALL_INF 128 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryW (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extract_cab_file (TYPE_1__*) ; 
 int /*<<< orphan*/  install_inf_file (TYPE_1__*) ; 
 int /*<<< orphan*/  setup_dll (TYPE_1__*) ; 

__attribute__((used)) static HRESULT install_cab_file(install_ctx_t *ctx)
{
    WCHAR tmp_path[MAX_PATH], tmp_dir[MAX_PATH];
    BOOL res = FALSE, leave_temp = FALSE;
    DWORD i;
    HRESULT hres;

    GetTempPathW(ARRAY_SIZE(tmp_path), tmp_path);

    for(i=0; !res && i < 100; i++) {
        GetTempFileNameW(tmp_path, NULL, GetTickCount() + i*17037, tmp_dir);
        res = CreateDirectoryW(tmp_dir, NULL);
    }
    if(!res)
        return E_FAIL;

    ctx->tmp_dir = tmp_dir;

    TRACE("Using temporary directory %s\n", debugstr_w(tmp_dir));

    hres = extract_cab_file(ctx);
    if(SUCCEEDED(hres)) {
        if(ctx->callback)
            IBindStatusCallback_OnProgress(ctx->callback, 0, 0, BINDSTATUS_INSTALLINGCOMPONENTS, ctx->install_file);

        switch(ctx->install_type) {
        case INSTALL_INF:
            hres = install_inf_file(ctx);
            break;
        case INSTALL_DLL:
            FIXME("Installing DLL, registering in temporary location\n");
            hres = setup_dll(ctx);
            if(SUCCEEDED(hres))
                leave_temp = TRUE;
            break;
        default:
            assert(0);
        }
    }

    if(!leave_temp)
        RemoveDirectoryW(ctx->tmp_dir);
    return hres;
}