#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_int_t ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_8__ {int extraline; scalar_t__ file_type; int /*<<< orphan*/ * f; scalar_t__ sent_end; scalar_t__ sent_begin; int /*<<< orphan*/  end_code_len; TYPE_2__ end_code; int /*<<< orphan*/  begin_code_len; TYPE_1__ begin_code; } ;
typedef  TYPE_3__ ngx_http_lua_clfactory_file_ctx_t ;
typedef  int ngx_flag_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  CLFACTORY_BEGIN_CODE ; 
 int /*<<< orphan*/  CLFACTORY_BEGIN_SIZE ; 
 int /*<<< orphan*/  CLFACTORY_END_CODE ; 
 int /*<<< orphan*/  CLFACTORY_END_SIZE ; 
 int EOF ; 
 int LUA_ERRFILE ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int* LUA_SIGNATURE ; 
 scalar_t__ NGX_LUA_BT_LJ ; 
 scalar_t__ NGX_LUA_BT_LUA ; 
 scalar_t__ NGX_LUA_TEXT_FILE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * freopen (char const*,char*,int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_findtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 int lua_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int ngx_http_lua_clfactory_bytecode_prepare (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int ngx_http_lua_clfactory_errfile (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ngx_http_lua_clfactory_getF ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

ngx_int_t
ngx_http_lua_clfactory_loadfile(lua_State *L, const char *filename)
{
    int                         c, status, readstatus;
    ngx_flag_t                  sharp;

    ngx_http_lua_clfactory_file_ctx_t        lf;

    /* index of filename on the stack */
    int                         fname_index;

    sharp = 0;
    fname_index = lua_gettop(L) + 1;

    lf.extraline = 0;
    lf.file_type = NGX_LUA_TEXT_FILE;

#ifndef OPENRESTY_LUAJIT
    lf.begin_code.ptr = CLFACTORY_BEGIN_CODE;
    lf.begin_code_len = CLFACTORY_BEGIN_SIZE;
    lf.end_code.ptr = CLFACTORY_END_CODE;
    lf.end_code_len = CLFACTORY_END_SIZE;
#endif

    lua_pushfstring(L, "@%s", filename);

    lf.f = fopen(filename, "r");
    if (lf.f == NULL) {
        return ngx_http_lua_clfactory_errfile(L, "open", fname_index);
    }

    c = getc(lf.f);

    if (c == '#') {  /* Unix exec. file? */
        lf.extraline = 1;

        while ((c = getc(lf.f)) != EOF && c != '\n') {
            /* skip first line */
        }

        if (c == '\n') {
            c = getc(lf.f);
        }

        sharp = 1;
    }

    if (c == LUA_SIGNATURE[0] && filename) {  /* binary file? */
        lf.f = freopen(filename, "rb", lf.f);  /* reopen in binary mode */

        if (lf.f == NULL) {
            return ngx_http_lua_clfactory_errfile(L, "reopen", fname_index);
        }

        /* check whether lib jit exists */
        luaL_findtable(L, LUA_REGISTRYINDEX, "_LOADED", 1);
        lua_getfield(L, -1, "jit");  /* get _LOADED["jit"] */

        if (lua_istable(L, -1)) {
            lf.file_type = NGX_LUA_BT_LJ;

        } else {
            lf.file_type = NGX_LUA_BT_LUA;
        }

        lua_pop(L, 2);

        /*
         * Loading bytecode with an extra header is disabled for security
         * reasons. This may circumvent the usual check for bytecode vs.
         * Lua code by looking at the first char. Since this is a potential
         * security violation no attempt is made to echo the chunkname either.
         */
        if (lf.file_type == NGX_LUA_BT_LJ && sharp) {

            if (filename) {
                fclose(lf.f);  /* close file (even in case of errors) */
            }

            filename = lua_tostring(L, fname_index) + 1;
            lua_pushfstring(L, "bad byte-code header in %s", filename);
            lua_remove(L, fname_index);

            return LUA_ERRFILE;
        }

        while ((c = getc(lf.f)) != EOF && c != LUA_SIGNATURE[0]) {
            /* skip eventual `#!...' */
        }

#ifndef OPENRESTY_LUAJIT
        status = ngx_http_lua_clfactory_bytecode_prepare(L, &lf, fname_index);

        if (status != 0) {
            return status;
        }
#endif

        lf.extraline = 0;
    }

#ifndef OPENRESTY_LUAJIT
    if (lf.file_type == NGX_LUA_TEXT_FILE) {
        ungetc(c, lf.f);
    }

    lf.sent_begin = lf.sent_end = 0;

#else
    ungetc(c, lf.f);
#endif
    status = lua_load(L, ngx_http_lua_clfactory_getF, &lf,
                      lua_tostring(L, -1));

    readstatus = ferror(lf.f);

    if (filename) {
        fclose(lf.f);  /* close file (even in case of errors) */
    }

    if (readstatus) {
        lua_settop(L, fname_index);  /* ignore results from `lua_load' */
        return ngx_http_lua_clfactory_errfile(L, "read", fname_index);
    }

    lua_remove(L, fname_index);

    return status;
}