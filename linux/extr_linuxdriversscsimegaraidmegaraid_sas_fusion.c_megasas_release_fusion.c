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
struct megasas_instance {int bar; int /*<<< orphan*/  pdev; int /*<<< orphan*/  reg_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megasas_free_cmds (struct megasas_instance*) ; 
 int /*<<< orphan*/  megasas_free_cmds_fusion (struct megasas_instance*) ; 
 int /*<<< orphan*/  megasas_free_ioc_init_cmd (struct megasas_instance*) ; 
 int /*<<< orphan*/  pci_release_selected_regions (int /*<<< orphan*/ ,int) ; 

void
megasas_release_fusion(struct megasas_instance *instance)
{
	megasas_free_ioc_init_cmd(instance);
	megasas_free_cmds(instance);
	megasas_free_cmds_fusion(instance);

	iounmap(instance->reg_set);

	pci_release_selected_regions(instance->pdev, 1<<instance->bar);
}