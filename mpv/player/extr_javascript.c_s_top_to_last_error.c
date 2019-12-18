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
 int /*<<< orphan*/  js_hasproperty (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ js_isobject (int /*<<< orphan*/ *,int) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_last_error (struct script_ctx*,int,char*) ; 

__attribute__((used)) static void s_top_to_last_error(struct script_ctx *ctx, js_State *J)
{
    set_last_error(ctx, 1, "unknown error");
    if (js_try(J))
        return;
    if (js_isobject(J, -1))
        js_hasproperty(J, -1, "stack");  // fetches it if exists
    set_last_error(ctx, 1, js_tostring(J, -1));
    js_endtry(J);
}