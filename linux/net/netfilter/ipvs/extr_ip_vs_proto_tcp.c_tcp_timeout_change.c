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
struct ip_vs_proto_data {int /*<<< orphan*/  tcp_state_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcp_states ; 
 int /*<<< orphan*/  tcp_states_dos ; 

__attribute__((used)) static void tcp_timeout_change(struct ip_vs_proto_data *pd, int flags)
{
	int on = (flags & 1);		/* secure_tcp */

	/*
	** FIXME: change secure_tcp to independent sysctl var
	** or make it per-service or per-app because it is valid
	** for most if not for all of the applications. Something
	** like "capabilities" (flags) for each object.
	*/
	pd->tcp_state_table = (on ? tcp_states_dos : tcp_states);
}