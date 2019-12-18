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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct thread {int dummy; } ;
struct symbol {int dummy; } ;
struct ip_callchain {scalar_t__* ips; } ;
struct callchain_cursor {int dummy; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
 scalar_t__ PERF_CONTEXT_MAX ; 
 int add_callchain_ip (struct thread*,struct callchain_cursor*,struct symbol**,struct addr_location*,int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_prev_cpumode(struct ip_callchain *chain, struct thread *thread,
			     struct callchain_cursor *cursor,
			     struct symbol **parent,
			     struct addr_location *root_al,
			     u8 *cpumode, int ent)
{
	int err = 0;

	while (--ent >= 0) {
		u64 ip = chain->ips[ent];

		if (ip >= PERF_CONTEXT_MAX) {
			err = add_callchain_ip(thread, cursor, parent,
					       root_al, cpumode, ip,
					       false, NULL, NULL, 0);
			break;
		}
	}
	return err;
}