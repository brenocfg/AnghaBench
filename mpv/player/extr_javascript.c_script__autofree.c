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
 int /*<<< orphan*/  js_currentfunction (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_getproperty (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_throw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_touserdata (int /*<<< orphan*/ *,int,char*) ; 
 int s_run_af_jsc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void script__autofree(js_State *J)
{
    // The target function is at the "af_" property of this function instance.
    js_currentfunction(J);
    js_getproperty(J, -1, "af_");
    af_CFunction fn = (af_CFunction)js_touserdata(J, -1, "af_fn");
    js_pop(J, 2);

    void *af = talloc_new(NULL);
    int r = s_run_af_jsc(J, fn, af);
    talloc_free(af);
    if (r)
        js_throw(J);
}