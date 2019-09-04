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
struct altera_msi {int /*<<< orphan*/  inner_domain; int /*<<< orphan*/  msi_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void altera_free_domains(struct altera_msi *msi)
{
	irq_domain_remove(msi->msi_domain);
	irq_domain_remove(msi->inner_domain);
}