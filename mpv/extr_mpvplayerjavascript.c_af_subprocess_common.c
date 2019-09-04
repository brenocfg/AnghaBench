#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  start; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  start; } ;
struct subprocess_cb_ctx {void* talloc_ctx; int max_size; TYPE_3__ err; TYPE_2__ output; int /*<<< orphan*/  log; } ;
struct script_ctx {int /*<<< orphan*/  log; TYPE_1__* mpctx; } ;
struct mp_cancel {int dummy; } ;
typedef  int /*<<< orphan*/  js_State ;
typedef  int int64_t ;
struct TYPE_4__ {struct mp_cancel* playback_abort; } ;

/* Variables and functions */
 int MP_ARRAY_SIZE (char**) ; 
 int MP_SUBPROCESS_EKILLED_BY_US ; 
 struct script_ctx* jctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_getindex (int /*<<< orphan*/ *,int,int) ; 
 int js_getlength (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_getproperty (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ js_hasproperty (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  js_isobject (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isundefined (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_newobject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_setproperty (int /*<<< orphan*/ *,int,char*) ; 
 int js_toboolean (int /*<<< orphan*/ *,int) ; 
 int js_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_tostring (int /*<<< orphan*/ *,int) ; 
 int mp_subprocess (char**,struct mp_cancel*,struct subprocess_cb_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  mp_subprocess_detached (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  push_success (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  subprocess_stderr ; 
 int /*<<< orphan*/  subprocess_stdout ; 
 char* talloc_strdup (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void af_subprocess_common(js_State *J, int detach, void *af)
{
    struct script_ctx *ctx = jctx(J);
    if (!js_isobject(J, 1))
        js_error(J, "argument must be an object");

    js_getproperty(J, 1, "args"); // args
    int num_args = js_getlength(J, -1);
    if (!num_args) // not using js_isarray to also accept array-like objects
        js_error(J, "args must be an non-empty array");
    char *args[256];
    if (num_args > MP_ARRAY_SIZE(args) - 1) // last needs to be NULL
        js_error(J, "too many arguments");
    if (num_args < 1)
        js_error(J, "program name missing");

    for (int n = 0; n < num_args; n++) {
        js_getindex(J, -1, n);
        if (js_isundefined(J, -1))
            js_error(J, "program arguments must be strings");
        args[n] = talloc_strdup(af, js_tostring(J, -1));
        js_pop(J, 1); // args
    }
    args[num_args] = NULL;

    if (detach) {
        mp_subprocess_detached(ctx->log, args);
        push_success(J);
        return;
    }

    struct mp_cancel *cancel = NULL;
    if (js_hasproperty(J, 1, "cancellable") ? js_toboolean(J, -1) : true)
        cancel = ctx->mpctx->playback_abort;

    int64_t max_size = js_hasproperty(J, 1, "max_size") ? js_tointeger(J, -1)
                                                        : 16 * 1024 * 1024;
    struct subprocess_cb_ctx cb_ctx = {
        .log = ctx->log,
        .talloc_ctx = af,
        .max_size = max_size,
    };

    char *error = NULL;
    int status = mp_subprocess(args, cancel, &cb_ctx, subprocess_stdout,
                               subprocess_stderr, &error);

    js_newobject(J); // res
    if (error) {
        js_pushstring(J, error); // res e
        js_setproperty(J, -2, "error"); // res
    }
    js_pushnumber(J, status); // res s
    js_setproperty(J, -2, "status"); // res
    js_pushlstring(J, cb_ctx.output.start, cb_ctx.output.len); // res d
    js_setproperty(J, -2, "stdout"); // res
    js_pushlstring(J, cb_ctx.err.start, cb_ctx.err.len);
    js_setproperty(J, -2, "stderr");
    js_pushboolean(J, status == MP_SUBPROCESS_EKILLED_BY_US); // res b
    js_setproperty(J, -2, "killed_by_us"); // res
}