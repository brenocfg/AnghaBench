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
struct pci_dev {int dummy; } ;
struct config_field {int dummy; } ;

/* Variables and functions */
 int xen_pcibk_config_add_field_offset (struct pci_dev*,struct config_field const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int xen_pcibk_config_add_field(struct pci_dev *dev,
					   const struct config_field *field)
{
	return xen_pcibk_config_add_field_offset(dev, field, 0);
}