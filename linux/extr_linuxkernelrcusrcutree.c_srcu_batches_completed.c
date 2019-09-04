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
struct srcu_struct {unsigned long srcu_idx; } ;

/* Variables and functions */

unsigned long srcu_batches_completed(struct srcu_struct *sp)
{
	return sp->srcu_idx;
}