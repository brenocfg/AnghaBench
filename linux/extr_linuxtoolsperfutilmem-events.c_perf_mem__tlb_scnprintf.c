#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_2__ {int mem_dtlb; } ;
struct mem_info {TYPE_1__ data_src; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 int PERF_MEM_TLB_HIT ; 
 int PERF_MEM_TLB_MISS ; 
 int PERF_MEM_TLB_NA ; 
 scalar_t__ scnprintf (char*,size_t,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char** tlb_access ; 

int perf_mem__tlb_scnprintf(char *out, size_t sz, struct mem_info *mem_info)
{
	size_t l = 0, i;
	u64 m = PERF_MEM_TLB_NA;
	u64 hit, miss;

	sz -= 1; /* -1 for null termination */
	out[0] = '\0';

	if (mem_info)
		m = mem_info->data_src.mem_dtlb;

	hit = m & PERF_MEM_TLB_HIT;
	miss = m & PERF_MEM_TLB_MISS;

	/* already taken care of */
	m &= ~(PERF_MEM_TLB_HIT|PERF_MEM_TLB_MISS);

	for (i = 0; m && i < ARRAY_SIZE(tlb_access); i++, m >>= 1) {
		if (!(m & 0x1))
			continue;
		if (l) {
			strcat(out, " or ");
			l += 4;
		}
		l += scnprintf(out + l, sz - l, tlb_access[i]);
	}
	if (*out == '\0')
		l += scnprintf(out, sz - l, "N/A");
	if (hit)
		l += scnprintf(out + l, sz - l, " hit");
	if (miss)
		l += scnprintf(out + l, sz - l, " miss");

	return l;
}