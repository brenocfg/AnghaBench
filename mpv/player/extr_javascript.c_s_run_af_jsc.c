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
typedef  int /*<<< orphan*/  (* af_CFunction ) (int /*<<< orphan*/ *,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s_run_af_jsc(js_State *J, af_CFunction fn, void *af)
{
    if (js_try(J))
        return 1;
    fn(J, af);
    js_endtry(J);
    return 0;
}