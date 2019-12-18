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
struct dummy_tracepoint_args {int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_ESTATS_TX_RESET ; 
 int /*<<< orphan*/  send_basic_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int _dummy_tracepoint(struct dummy_tracepoint_args *arg)
{
	if (!arg->sock)
		return 0;

	send_basic_event(arg->sock, TCP_ESTATS_TX_RESET);
	return 0;
}