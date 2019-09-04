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
struct regs_dump {size_t abi; } ;

/* Variables and functions */
 size_t PERF_SAMPLE_REGS_ABI_64 ; 
 char const** regs_abi ; 

__attribute__((used)) static inline const char *regs_dump_abi(struct regs_dump *d)
{
	if (d->abi > PERF_SAMPLE_REGS_ABI_64)
		return "unknown";

	return regs_abi[d->abi];
}