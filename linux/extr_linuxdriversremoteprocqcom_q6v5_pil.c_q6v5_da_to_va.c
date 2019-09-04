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
struct rproc {struct q6v5* priv; } ;
struct q6v5 {int mpss_reloc; int mpss_size; void* mpss_region; } ;

/* Variables and functions */

__attribute__((used)) static void *q6v5_da_to_va(struct rproc *rproc, u64 da, int len)
{
	struct q6v5 *qproc = rproc->priv;
	int offset;

	offset = da - qproc->mpss_reloc;
	if (offset < 0 || offset + len > qproc->mpss_size)
		return NULL;

	return qproc->mpss_region + offset;
}