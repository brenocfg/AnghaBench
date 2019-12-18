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
 int /*<<< orphan*/  js_error (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ js_isundefined (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 double js_tonumber (int /*<<< orphan*/ *,int) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_format_time_fmt (char const*,double) ; 
 char* talloc_steal (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void script_format_time(js_State *J, void *af)
{
    double t = js_tonumber(J, 1);
    const char *fmt = js_isundefined(J, 2) ? "%H:%M:%S" : js_tostring(J, 2);
    char *r = talloc_steal(af, mp_format_time_fmt(fmt, t));
    if (!r)
        js_error(J, "Invalid time format string '%s'", fmt);
    js_pushstring(J, r);
}