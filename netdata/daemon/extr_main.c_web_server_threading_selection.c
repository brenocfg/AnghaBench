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
struct TYPE_2__ {scalar_t__ start_routine; int enabled; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SECTION_WEB ; 
 scalar_t__ WEB_SERVER_MODE_STATIC_THREADED ; 
 int /*<<< orphan*/  config_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ socket_listen_main_static_threaded ; 
 TYPE_1__* static_threads ; 
 scalar_t__ web_server_mode ; 
 scalar_t__ web_server_mode_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  web_server_mode_name (scalar_t__) ; 

void web_server_threading_selection(void) {
    web_server_mode = web_server_mode_id(config_get(CONFIG_SECTION_WEB, "mode", web_server_mode_name(web_server_mode)));

    int static_threaded = (web_server_mode == WEB_SERVER_MODE_STATIC_THREADED);

    int i;
    for (i = 0; static_threads[i].name; i++) {
        if (static_threads[i].start_routine == socket_listen_main_static_threaded)
            static_threads[i].enabled = static_threaded;
    }
}