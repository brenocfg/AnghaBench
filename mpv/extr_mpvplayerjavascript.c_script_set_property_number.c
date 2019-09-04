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
typedef  int /*<<< orphan*/  mpv_handle ;
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_FORMAT_DOUBLE ; 
 int /*<<< orphan*/ * jclient (int /*<<< orphan*/ *) ; 
 double js_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_tostring (int /*<<< orphan*/ *,int) ; 
 int mpv_set_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  push_status (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void script_set_property_number(js_State *J)
{
    double v = js_tonumber(J, 2);
    mpv_handle *h = jclient(J);
    int e = mpv_set_property(h, js_tostring(J, 1), MPV_FORMAT_DOUBLE, &v);
    push_status(J, e);
}