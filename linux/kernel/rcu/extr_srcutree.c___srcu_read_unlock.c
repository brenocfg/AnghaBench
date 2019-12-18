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
struct srcu_struct {TYPE_1__* sda; } ;
struct TYPE_2__ {int /*<<< orphan*/ * srcu_unlock_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 

void __srcu_read_unlock(struct srcu_struct *ssp, int idx)
{
	smp_mb(); /* C */  /* Avoid leaking the critical section. */
	this_cpu_inc(ssp->sda->srcu_unlock_count[idx]);
}