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
typedef  enum conn_states { ____Placeholder_conn_states } conn_states ;

/* Variables and functions */

__attribute__((used)) static const char *state_text(enum conn_states state) {
    const char* const statenames[] = { "conn_listening",
                                       "conn_new_cmd",
                                       "conn_waiting",
                                       "conn_read",
                                       "conn_parse_cmd",
                                       "conn_write",
                                       "conn_nread",
                                       "conn_swallow",
                                       "conn_closing",
                                       "conn_mwrite",
                                       "conn_closed",
                                       "conn_watch" };
    return statenames[state];
}