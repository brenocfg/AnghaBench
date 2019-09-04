#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct TYPE_5__ {int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct TYPE_7__ {int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct TYPE_8__ {TYPE_2__ dw; TYPE_1__ w; TYPE_3__ b; } ;
struct config_field {int size; TYPE_4__ u; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  xen_pcibk_config_add_field (struct pci_dev*,struct config_field*) ; 
 int /*<<< orphan*/  xen_pcibk_read_config_byte ; 
 int /*<<< orphan*/  xen_pcibk_read_config_dword ; 
 int /*<<< orphan*/  xen_pcibk_read_config_word ; 
 int /*<<< orphan*/  xen_pcibk_write_config_byte ; 
 int /*<<< orphan*/  xen_pcibk_write_config_dword ; 
 int /*<<< orphan*/  xen_pcibk_write_config_word ; 

int xen_pcibk_config_quirks_add_field(struct pci_dev *dev, struct config_field
				    *field)
{
	int err = 0;

	switch (field->size) {
	case 1:
		field->u.b.read = xen_pcibk_read_config_byte;
		field->u.b.write = xen_pcibk_write_config_byte;
		break;
	case 2:
		field->u.w.read = xen_pcibk_read_config_word;
		field->u.w.write = xen_pcibk_write_config_word;
		break;
	case 4:
		field->u.dw.read = xen_pcibk_read_config_dword;
		field->u.dw.write = xen_pcibk_write_config_dword;
		break;
	default:
		err = -EINVAL;
		goto out;
	}

	xen_pcibk_config_add_field(dev, field);

out:
	return err;
}