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
struct dl_bw {int bw; int total_bw; } ;

/* Variables and functions */

__attribute__((used)) static inline
bool __dl_overflow(struct dl_bw *dl_b, int cpus, u64 old_bw, u64 new_bw)
{
	return dl_b->bw != -1 &&
	       dl_b->bw * cpus < dl_b->total_bw - old_bw + new_bw;
}