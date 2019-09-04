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
 int /*<<< orphan*/  js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpv_command_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void script_command(js_State *J)
{
    push_status(J, mpv_command_string(jclient(J), js_tostring(J, 1)));
}