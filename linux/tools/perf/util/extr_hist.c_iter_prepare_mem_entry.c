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
struct perf_sample {int dummy; } ;
struct mem_info {int dummy; } ;
struct hist_entry_iter {struct mem_info* priv; struct perf_sample* sample; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mem_info* sample__resolve_mem (struct perf_sample*,struct addr_location*) ; 

__attribute__((used)) static int
iter_prepare_mem_entry(struct hist_entry_iter *iter, struct addr_location *al)
{
	struct perf_sample *sample = iter->sample;
	struct mem_info *mi;

	mi = sample__resolve_mem(sample, al);
	if (mi == NULL)
		return -ENOMEM;

	iter->priv = mi;
	return 0;
}