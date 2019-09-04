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
struct script_ctx {char* filename; } ;
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  add_functions (int /*<<< orphan*/ *,struct script_ctx*) ; 
 struct script_ctx* jctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_hasproperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  js_iscallable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_loadstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  norm_err_proto_js ; 
 int /*<<< orphan*/  run_file (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void script__run_script(js_State *J)
{
    js_loadstring(J, "@/norm_err.js", norm_err_proto_js);
    js_copy(J, 0);
    js_pcall(J, 0);

    struct script_ctx *ctx = jctx(J);
    add_functions(J, ctx);
    run_file(J, "@/defaults.js");
    run_file(J, ctx->filename);  // the main file to run

    if (!js_hasproperty(J, 0, "mp_event_loop") || !js_iscallable(J, -1))
        js_error(J, "no event loop function");
    js_copy(J, 0);
    js_call(J, 0); // mp_event_loop
}