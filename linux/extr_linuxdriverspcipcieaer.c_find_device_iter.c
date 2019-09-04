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
struct aer_err_info {int /*<<< orphan*/  multi_error_valid; } ;

/* Variables and functions */
 scalar_t__ add_error_device (struct aer_err_info*,struct pci_dev*) ; 
 scalar_t__ is_error_source (struct pci_dev*,struct aer_err_info*) ; 

__attribute__((used)) static int find_device_iter(struct pci_dev *dev, void *data)
{
	struct aer_err_info *e_info = (struct aer_err_info *)data;

	if (is_error_source(dev, e_info)) {
		/* List this device */
		if (add_error_device(e_info, dev)) {
			/* We cannot handle more... Stop iteration */
			/* TODO: Should print error message here? */
			return 1;
		}

		/* If there is only a single error, stop iteration */
		if (!e_info->multi_error_valid)
			return 1;
	}
	return 0;
}