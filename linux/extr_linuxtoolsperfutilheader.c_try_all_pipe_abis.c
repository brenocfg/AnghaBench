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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ u64 ;
struct perf_header {int needs_swap; } ;

/* Variables and functions */
 scalar_t__* attr_pipe_abi_sizes ; 
 scalar_t__ bswap_64 (scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int try_all_pipe_abis(uint64_t hdr_sz, struct perf_header *ph)
{
	u64 attr_size;
	int i;

	for (i = 0 ; attr_pipe_abi_sizes[i]; i++) {
		if (hdr_sz != attr_pipe_abi_sizes[i]) {
			attr_size = bswap_64(hdr_sz);
			if (attr_size != hdr_sz)
				continue;

			ph->needs_swap = true;
		}
		pr_debug("Pipe ABI%d perf.data file detected\n", i);
		return 0;
	}
	return -1;
}