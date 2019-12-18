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
struct event_timeout {int dummy; } ;

/* Variables and functions */
 int event_timeout_remaining (struct event_timeout*) ; 
 int max_int (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_time () ; 

int
get_server_poll_remaining_time(struct event_timeout *server_poll_timeout)
{
    update_time();
    int remaining = event_timeout_remaining(server_poll_timeout);
    return max_int(0, remaining);
}