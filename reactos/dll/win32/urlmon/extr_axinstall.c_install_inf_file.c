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
struct TYPE_4__ {int /*<<< orphan*/  tmp_dir; int /*<<< orphan*/  install_file; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ install_ctx_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetPrivateProfileStringW (char const*,char const*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSC_FLAG_INF ; 
 int /*<<< orphan*/  RunSetupCommandW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 int /*<<< orphan*/  process_hook_section (TYPE_1__*,char*) ; 
 scalar_t__ strlenW (char const*) ; 

__attribute__((used)) static HRESULT install_inf_file(install_ctx_t *ctx)
{
    WCHAR buf[2048], sect_name[128];
    BOOL default_install = TRUE;
    const WCHAR *key;
    DWORD len;
    HRESULT hres;

    static const WCHAR setup_hooksW[] = {'S','e','t','u','p',' ','H','o','o','k','s',0};
    static const WCHAR add_codeW[] = {'A','d','d','.','C','o','d','e',0};

    len = GetPrivateProfileStringW(setup_hooksW, NULL, NULL, buf, ARRAY_SIZE(buf), ctx->install_file);
    if(len) {
        default_install = FALSE;

        for(key = buf; *key; key += strlenW(key)+1) {
            TRACE("[Setup Hooks] key: %s\n", debugstr_w(key));

            len = GetPrivateProfileStringW(setup_hooksW, key, NULL, sect_name, ARRAY_SIZE(sect_name),
                    ctx->install_file);
            if(!len) {
                WARN("Could not get key value\n");
                return E_FAIL;
            }

            hres = process_hook_section(ctx, sect_name);
            if(FAILED(hres))
                return hres;
        }
    }

    len = GetPrivateProfileStringW(add_codeW, NULL, NULL, buf, ARRAY_SIZE(buf), ctx->install_file);
    if(len) {
        default_install = FALSE;

        for(key = buf; *key; key += strlenW(key)+1) {
            TRACE("[Add.Code] key: %s\n", debugstr_w(key));

            len = GetPrivateProfileStringW(add_codeW, key, NULL, sect_name, ARRAY_SIZE(sect_name),
                    ctx->install_file);
            if(!len) {
                WARN("Could not get key value\n");
                return E_FAIL;
            }

            hres = RunSetupCommandW(ctx->hwnd, ctx->install_file, sect_name,
                    ctx->tmp_dir, NULL, NULL, RSC_FLAG_INF, NULL);
            if(FAILED(hres)) {
                WARN("RunSetupCommandW failed: %08x\n", hres);
                return hres;
            }
        }
    }

    if(default_install) {
        hres = RunSetupCommandW(ctx->hwnd, ctx->install_file, NULL, ctx->tmp_dir, NULL, NULL, RSC_FLAG_INF, NULL);
        if(FAILED(hres)) {
            WARN("RunSetupCommandW failed: %08x\n", hres);
            return hres;
        }
    }

    return S_OK;
}