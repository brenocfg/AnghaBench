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
typedef  int /*<<< orphan*/  js_State ;
typedef  int /*<<< orphan*/  af_CFunction ;

/* Variables and functions */
 int JS_DONTCONF ; 
 int JS_DONTENUM ; 
 int JS_READONLY ; 
 int /*<<< orphan*/  js_defproperty (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  js_newcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  js_newuserdata (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushnull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  script__autofree ; 

__attribute__((used)) static void af_newcfunction(js_State *J, af_CFunction fn, const char *name,
                            int length)
{
    js_newcfunction(J, script__autofree, name, length);
    js_pushnull(J);  // a prototype for the userdata object
    js_newuserdata(J, "af_fn", fn, NULL);  // uses a "af_fn" verification tag
    js_defproperty(J, -2, "af_", JS_READONLY | JS_DONTENUM | JS_DONTCONF);
}