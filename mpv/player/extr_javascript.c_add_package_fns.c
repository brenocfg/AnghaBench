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
struct fn_entry {char const* name; int /*<<< orphan*/  length; int /*<<< orphan*/  afc_fn; scalar_t__ jsc_fn; } ;
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  af_newcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_newcfunction (int /*<<< orphan*/ *,scalar_t__,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_newobject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_setproperty (int /*<<< orphan*/ *,int,char const*) ; 

__attribute__((used)) static void add_package_fns(js_State *J, const char *module,
                            const struct fn_entry *e)
{
    js_newobject(J);
    for (int n = 0; e[n].name; n++) {
        if (e[n].jsc_fn) {
            js_newcfunction(J, e[n].jsc_fn, e[n].name, e[n].length);
        } else {
            af_newcfunction(J, e[n].afc_fn, e[n].name, e[n].length);
        }
        js_setproperty(J, -2, e[n].name);
    }
    js_setproperty(J, -2, module);
}