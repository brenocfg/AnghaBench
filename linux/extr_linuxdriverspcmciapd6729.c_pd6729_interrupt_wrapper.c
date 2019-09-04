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
struct timer_list {int dummy; } ;
struct pd6729_socket {int /*<<< orphan*/  poll_timer; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 struct pd6729_socket* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pd6729_interrupt (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  poll_timer ; 
 struct pd6729_socket* socket ; 

__attribute__((used)) static void pd6729_interrupt_wrapper(struct timer_list *t)
{
	struct pd6729_socket *socket = from_timer(socket, t, poll_timer);

	pd6729_interrupt(0, (void *)socket);
	mod_timer(&socket->poll_timer, jiffies + HZ);
}