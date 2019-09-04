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
struct qbman_release_desc {int verb; } ;

/* Variables and functions */

void qbman_release_desc_set_rcdi(struct qbman_release_desc *d, int enable)
{
	if (enable)
		d->verb |= 1 << 6;
	else
		d->verb &= ~(1 << 6);
}