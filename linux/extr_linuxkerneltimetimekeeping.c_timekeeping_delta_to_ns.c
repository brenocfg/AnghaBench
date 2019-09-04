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
typedef  int u64 ;
struct tk_read_base {int mult; int xtime_nsec; int shift; } ;

/* Variables and functions */
 int arch_gettimeoffset () ; 

__attribute__((used)) static inline u64 timekeeping_delta_to_ns(const struct tk_read_base *tkr, u64 delta)
{
	u64 nsec;

	nsec = delta * tkr->mult + tkr->xtime_nsec;
	nsec >>= tkr->shift;

	/* If arch requires, add in get_arch_timeoffset() */
	return nsec + arch_gettimeoffset();
}