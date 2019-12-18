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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf1 (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dump_mem(void *dumpme, int len_bytes)
{
	char *c = (void *)dumpme;
	int i;

	for (i = 0; i < len_bytes; i += sizeof(u64)) {
		u64 *ptr = (u64 *)(c + i);
		dprintf1("dump[%03d][@%p]: %016jx\n", i, ptr, *ptr);
	}
}