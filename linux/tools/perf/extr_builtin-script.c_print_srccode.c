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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u8 ;
struct thread {int /*<<< orphan*/  srccode_state; } ;
struct addr_location {int /*<<< orphan*/  addr; int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  al ;

/* Variables and functions */
 int map__fprintf_srccode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct addr_location*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  thread__find_map (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addr_location*) ; 

__attribute__((used)) static int print_srccode(struct thread *thread, u8 cpumode, uint64_t addr)
{
	struct addr_location al;
	int ret = 0;

	memset(&al, 0, sizeof(al));
	thread__find_map(thread, cpumode, addr, &al);
	if (!al.map)
		return 0;
	ret = map__fprintf_srccode(al.map, al.addr, stdout,
		    &thread->srccode_state);
	if (ret)
		ret += printf("\n");
	return ret;
}