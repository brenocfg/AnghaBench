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
 int /*<<< orphan*/  MPV_FORMAT_DOUBLE ; 
 int /*<<< orphan*/  jclient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,double) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int mpv_get_property (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  pushed_error (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void script_get_property_number(js_State *J)
{
    double result;
    const char *name = js_tostring(J, 1);
    int e = mpv_get_property(jclient(J), name, MPV_FORMAT_DOUBLE, &result);
    if (!pushed_error(J, e, 2))
        js_pushnumber(J, result);
}