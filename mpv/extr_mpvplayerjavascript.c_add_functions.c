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
struct script_ctx {int /*<<< orphan*/  filename; int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  add_package_fns (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_getproperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_setproperty (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  main_fns ; 
 int /*<<< orphan*/  mpv_client_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utils_fns ; 

__attribute__((used)) static void add_functions(js_State *J, struct script_ctx *ctx)
{
    js_copy(J, 0);
    add_package_fns(J, "mp", main_fns);
    js_getproperty(J, 0, "mp");  // + this mp
    add_package_fns(J, "utils", utils_fns);

    js_pushstring(J, mpv_client_name(ctx->client));
    js_setproperty(J, -2, "script_name");

    js_pushstring(J, ctx->filename);
    js_setproperty(J, -2, "script_file");

    js_pop(J, 2);  // leave the stack as we got it
}