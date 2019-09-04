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
 int MP_ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  MP_CMD_MAX_ARGS ; 
 int /*<<< orphan*/  jclient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_error (int /*<<< orphan*/ *,char*) ; 
 int js_gettop (int /*<<< orphan*/ *) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpv_command (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  push_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void script_commandv(js_State *J)
{
    const char *argv[MP_CMD_MAX_ARGS + 1];
    int length = js_gettop(J) - 1;
    if (length >= MP_ARRAY_SIZE(argv))
        js_error(J, "Too many arguments");

    for (int i = 0; i < length; i++)
        argv[i] = js_tostring(J, 1 + i);
    argv[length] = NULL;
    push_status(J, mpv_command(jclient(J), argv));
}