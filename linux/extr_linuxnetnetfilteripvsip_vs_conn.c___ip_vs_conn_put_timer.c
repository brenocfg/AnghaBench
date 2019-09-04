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
struct ip_vs_conn {int flags; unsigned long timeout; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int IP_VS_CONN_F_ONE_PACKET ; 
 int /*<<< orphan*/  __ip_vs_conn_put (struct ip_vs_conn*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void __ip_vs_conn_put_timer(struct ip_vs_conn *cp)
{
	unsigned long t = (cp->flags & IP_VS_CONN_F_ONE_PACKET) ?
		0 : cp->timeout;
	mod_timer(&cp->timer, jiffies+t);

	__ip_vs_conn_put(cp);
}