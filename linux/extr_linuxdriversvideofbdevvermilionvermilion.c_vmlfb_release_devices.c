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
struct vml_par {int /*<<< orphan*/  vdc; int /*<<< orphan*/  gpu; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmlfb_release_devices(struct vml_par *par)
{
	if (atomic_dec_and_test(&par->refcount)) {
		pci_disable_device(par->gpu);
		pci_disable_device(par->vdc);
	}
}