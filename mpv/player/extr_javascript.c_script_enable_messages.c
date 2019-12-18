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
 int /*<<< orphan*/  js_error (int /*<<< orphan*/ *,char*,char const*) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ mp_msg_find_level (char const*) ; 
 int /*<<< orphan*/  mpv_request_log_messages (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  push_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void script_enable_messages(js_State *J)
{
    const char *level = js_tostring(J, 1);
    if (mp_msg_find_level(level) < 0)
        js_error(J, "Invalid log level '%s'", level);
    push_status(J, mpv_request_log_messages(jclient(J), level));
}