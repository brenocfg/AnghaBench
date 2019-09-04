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
 int js_toboolean (int /*<<< orphan*/ *,int) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 char* mpv_event_name (int) ; 
 int /*<<< orphan*/  mpv_request_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  push_failure (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  push_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static void script__request_event(js_State *J)
{
    const char *event = js_tostring(J, 1);
    bool enable = js_toboolean(J, 2);

    const char *name;
    for (int n = 0; n < 256 && (name = mpv_event_name(n)); n++) {
        if (strcmp(name, event) == 0) {
            push_status(J, mpv_request_event(jclient(J), n, enable));
            return;
        }
    }
    push_failure(J, "Unknown event name");
}