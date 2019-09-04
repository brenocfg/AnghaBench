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
struct TYPE_2__ {unsigned long num_cpus; } ;

/* Variables and functions */
 TYPE_1__ xgene_msi_ctrl ; 

__attribute__((used)) static int hwirq_to_cpu(unsigned long hwirq)
{
	return (hwirq % xgene_msi_ctrl.num_cpus);
}