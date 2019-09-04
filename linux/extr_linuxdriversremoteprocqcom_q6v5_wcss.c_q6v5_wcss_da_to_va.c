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
struct rproc {struct q6v5_wcss* priv; } ;
struct q6v5_wcss {int mem_reloc; int mem_size; void* mem_region; } ;

/* Variables and functions */

__attribute__((used)) static void *q6v5_wcss_da_to_va(struct rproc *rproc, u64 da, int len)
{
	struct q6v5_wcss *wcss = rproc->priv;
	int offset;

	offset = da - wcss->mem_reloc;
	if (offset < 0 || offset + len > wcss->mem_size)
		return NULL;

	return wcss->mem_region + offset;
}