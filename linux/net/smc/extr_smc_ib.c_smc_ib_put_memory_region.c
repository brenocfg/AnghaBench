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
struct ib_mr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dereg_mr (struct ib_mr*) ; 

void smc_ib_put_memory_region(struct ib_mr *mr)
{
	ib_dereg_mr(mr);
}