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
struct pcie_port {int /*<<< orphan*/  num_vectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_MSI_IRQS ; 

__attribute__((used)) static void dw_plat_set_num_vectors(struct pcie_port *pp)
{
	pp->num_vectors = MAX_MSI_IRQS;
}