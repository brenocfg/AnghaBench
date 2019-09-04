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

/* Variables and functions */
 int /*<<< orphan*/  js_error (int /*<<< orphan*/ *,char*,char const*,char const*) ; 
 scalar_t__ js_isundefined (int /*<<< orphan*/ *,int) ; 
 char const* js_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int checkopt(js_State *J, int idx, const char *def, const char *opts[],
                    const char *desc)
{
    const char *opt = js_isundefined(J, idx) ? def : js_tostring(J, idx);
    for (int i = 0; opts[i]; i++) {
        if (strcmp(opt, opts[i]) == 0)
            return i;
    }
    js_error(J, "Invalid %s '%s'", desc, opt);
}