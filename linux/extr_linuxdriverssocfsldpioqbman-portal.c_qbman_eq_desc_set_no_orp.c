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
struct qbman_eq_desc {int verb; } ;

/* Variables and functions */
 int QB_ENQUEUE_CMD_ORP_ENABLE_SHIFT ; 
 int enqueue_rejects_to_fq ; 
 int enqueue_response_always ; 

void qbman_eq_desc_set_no_orp(struct qbman_eq_desc *d, int respond_success)
{
	d->verb &= ~(1 << QB_ENQUEUE_CMD_ORP_ENABLE_SHIFT);
	if (respond_success)
		d->verb |= enqueue_response_always;
	else
		d->verb |= enqueue_rejects_to_fq;
}