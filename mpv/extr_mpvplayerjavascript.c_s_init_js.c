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
struct script_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_newcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushglobal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_setcontext (int /*<<< orphan*/ *,struct script_ctx*) ; 
 int /*<<< orphan*/  js_setreport (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  report_handler ; 
 int /*<<< orphan*/  script__run_script ; 

__attribute__((used)) static int s_init_js(js_State *J, struct script_ctx *ctx)
{
    if (js_try(J))
        return 1;
    js_setcontext(J, ctx);
    js_setreport(J, report_handler);
    js_newcfunction(J, script__run_script, "run_script", 0);
    js_pushglobal(J);  // 'this' for script__run_script
    js_endtry(J);
    return 0;
}