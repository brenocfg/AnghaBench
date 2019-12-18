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
struct TYPE_2__ {int mem_lvl; int mem_lvl_num; scalar_t__ mem_remote; } ;
struct mem_info {TYPE_1__ data_src; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 int PERF_MEM_LVL_HIT ; 
 int PERF_MEM_LVL_MISS ; 
 int PERF_MEM_LVL_NA ; 
 char** mem_lvl ; 
 char** mem_lvlnum ; 
 scalar_t__ scnprintf (char*,size_t,char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

int perf_mem__lvl_scnprintf(char *out, size_t sz, struct mem_info *mem_info)
{
	size_t i, l = 0;
	u64 m =  PERF_MEM_LVL_NA;
	u64 hit, miss;
	int printed;

	if (mem_info)
		m  = mem_info->data_src.mem_lvl;

	sz -= 1; /* -1 for null termination */
	out[0] = '\0';

	hit = m & PERF_MEM_LVL_HIT;
	miss = m & PERF_MEM_LVL_MISS;

	/* already taken care of */
	m &= ~(PERF_MEM_LVL_HIT|PERF_MEM_LVL_MISS);


	if (mem_info && mem_info->data_src.mem_remote) {
		strcat(out, "Remote ");
		l += 7;
	}

	printed = 0;
	for (i = 0; m && i < ARRAY_SIZE(mem_lvl); i++, m >>= 1) {
		if (!(m & 0x1))
			continue;
		if (printed++) {
			strcat(out, " or ");
			l += 4;
		}
		l += scnprintf(out + l, sz - l, mem_lvl[i]);
	}

	if (mem_info && mem_info->data_src.mem_lvl_num) {
		int lvl = mem_info->data_src.mem_lvl_num;
		if (printed++) {
			strcat(out, " or ");
			l += 4;
		}
		if (mem_lvlnum[lvl])
			l += scnprintf(out + l, sz - l, mem_lvlnum[lvl]);
		else
			l += scnprintf(out + l, sz - l, "L%d", lvl);
	}

	if (l == 0)
		l += scnprintf(out + l, sz - l, "N/A");
	if (hit)
		l += scnprintf(out + l, sz - l, " hit");
	if (miss)
		l += scnprintf(out + l, sz - l, " miss");

	return l;
}