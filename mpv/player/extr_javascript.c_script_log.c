#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mp_log {int dummy; } ;
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_2__ {struct mp_log* log; } ;

/* Variables and functions */
 TYPE_1__* jctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int js_gettop (int /*<<< orphan*/ *) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_msg (struct mp_log*,int,char*,...) ; 
 int mp_msg_find_level (char const*) ; 
 int /*<<< orphan*/  push_success (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void script_log(js_State *J)
{
    const char *level = js_tostring(J, 1);
    int msgl = mp_msg_find_level(level);
    if (msgl < 0)
        js_error(J, "Invalid log level '%s'", level);

    struct mp_log *log = jctx(J)->log;
    for (int top = js_gettop(J), i = 2; i < top; i++)
        mp_msg(log, msgl, (i == 2 ? "%s" : " %s"), js_tostring(J, i));
    mp_msg(log, msgl, "\n");
    push_success(J);
}