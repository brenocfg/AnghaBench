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
 int /*<<< orphan*/  jclient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,double) ; 
 double mpv_get_time_us (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void script_get_time_ms(js_State *J)
{
    js_pushnumber(J, mpv_get_time_us(jclient(J)) / (double)(1000));
}