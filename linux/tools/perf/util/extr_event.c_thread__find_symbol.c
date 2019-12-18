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
typedef  int /*<<< orphan*/  u64 ;
struct thread {int dummy; } ;
struct symbol {int dummy; } ;
struct addr_location {struct symbol* sym; int /*<<< orphan*/  addr; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 struct symbol* map__find_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ thread__find_map (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addr_location*) ; 

struct symbol *thread__find_symbol(struct thread *thread, u8 cpumode,
				   u64 addr, struct addr_location *al)
{
	al->sym = NULL;
	if (thread__find_map(thread, cpumode, addr, al))
		al->sym = map__find_symbol(al->map, al->addr);
	return al->sym;
}