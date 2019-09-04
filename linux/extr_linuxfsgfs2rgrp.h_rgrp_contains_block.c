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
typedef  scalar_t__ u64 ;
struct gfs2_rgrpd {scalar_t__ rd_data0; scalar_t__ rd_data; } ;

/* Variables and functions */

__attribute__((used)) static inline int rgrp_contains_block(struct gfs2_rgrpd *rgd, u64 block)
{
	u64 first = rgd->rd_data0;
	u64 last = first + rgd->rd_data;
	return first <= block && block < last;
}