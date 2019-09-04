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
typedef  scalar_t__ u8 ;
struct qbman_pull_desc {scalar_t__ numf; } ;

/* Variables and functions */

void qbman_pull_desc_set_numframes(struct qbman_pull_desc *d, u8 numframes)
{
	d->numf = numframes - 1;
}