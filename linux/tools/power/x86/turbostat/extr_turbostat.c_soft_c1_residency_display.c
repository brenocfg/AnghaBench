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

/* Variables and functions */
 int /*<<< orphan*/  BIC_CPU_c1 ; 
 int /*<<< orphan*/  DO_BIC (int /*<<< orphan*/ ) ; 
 int DO_BIC_READ (int) ; 
 scalar_t__ use_c1_residency_msr ; 

int soft_c1_residency_display(int bic)
{
	if (!DO_BIC(BIC_CPU_c1) || use_c1_residency_msr)
		return 0;

	return DO_BIC_READ(bic);
}