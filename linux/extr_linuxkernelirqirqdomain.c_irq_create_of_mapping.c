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
struct of_phandle_args {int dummy; } ;
struct irq_fwspec {int dummy; } ;

/* Variables and functions */
 unsigned int irq_create_fwspec_mapping (struct irq_fwspec*) ; 
 int /*<<< orphan*/  of_phandle_args_to_fwspec (struct of_phandle_args*,struct irq_fwspec*) ; 

unsigned int irq_create_of_mapping(struct of_phandle_args *irq_data)
{
	struct irq_fwspec fwspec;

	of_phandle_args_to_fwspec(irq_data, &fwspec);
	return irq_create_fwspec_mapping(&fwspec);
}