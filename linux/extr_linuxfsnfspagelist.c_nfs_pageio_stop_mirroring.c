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
struct nfs_pageio_descriptor {int pg_mirror_count; scalar_t__ pg_mirror_idx; } ;

/* Variables and functions */

void nfs_pageio_stop_mirroring(struct nfs_pageio_descriptor *pgio)
{
	pgio->pg_mirror_count = 1;
	pgio->pg_mirror_idx = 0;
}