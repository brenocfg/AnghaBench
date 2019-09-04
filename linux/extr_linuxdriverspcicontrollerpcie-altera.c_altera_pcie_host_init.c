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
struct altera_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  altera_pcie_retrain (struct altera_pcie*) ; 

__attribute__((used)) static void altera_pcie_host_init(struct altera_pcie *pcie)
{
	altera_pcie_retrain(pcie);
}