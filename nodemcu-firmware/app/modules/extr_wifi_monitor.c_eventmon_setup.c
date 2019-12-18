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

/* Variables and functions */
 int /*<<< orphan*/  wifi_event_monitor_handle_event_cb ; 
 int /*<<< orphan*/  wifi_set_event_handler_cb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eventmon_setup() {
  wifi_set_event_handler_cb(wifi_event_monitor_handle_event_cb);
}