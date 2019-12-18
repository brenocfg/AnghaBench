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
struct TYPE_4__ {int /*<<< orphan*/  tmp_dir; int /*<<< orphan*/  hwnd; int /*<<< orphan*/  install_file; } ;
typedef  TYPE_1__ install_ctx_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ GetPrivateProfileStringW (char const*,char const*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RunSetupCommandW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 int /*<<< orphan*/  expand_command (TYPE_1__*,char*,char*,size_t*) ; 
 char* heap_alloc (size_t) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  strcmpiW (char const*,char const*) ; 
 scalar_t__ strlenW (char const*) ; 

__attribute__((used)) static HRESULT process_hook_section(install_ctx_t *ctx, const WCHAR *sect_name)
{
    WCHAR buf[2048], val[2*MAX_PATH];
    const WCHAR *key;
    DWORD len;
    HRESULT hres;

    static const WCHAR runW[] = {'r','u','n',0};

    len = GetPrivateProfileStringW(sect_name, NULL, NULL, buf, ARRAY_SIZE(buf), ctx->install_file);
    if(!len)
        return S_OK;

    for(key = buf; *key; key += strlenW(key)+1) {
        if(!strcmpiW(key, runW)) {
            WCHAR *cmd;
            size_t size;

            len = GetPrivateProfileStringW(sect_name, runW, NULL, val, ARRAY_SIZE(val), ctx->install_file);

            TRACE("Run %s\n", debugstr_w(val));

            expand_command(ctx, val, NULL, &size);

            cmd = heap_alloc(size*sizeof(WCHAR));
            if(!cmd)
                heap_free(cmd);

            expand_command(ctx, val, cmd, &size);
            hres = RunSetupCommandW(ctx->hwnd, cmd, NULL, ctx->tmp_dir, NULL, NULL, 0, NULL);
            heap_free(cmd);
            if(FAILED(hres))
                return hres;
        }else {
            FIXME("Unsupported hook %s\n", debugstr_w(key));
            return E_NOTIMPL;
        }
    }

    return S_OK;
}