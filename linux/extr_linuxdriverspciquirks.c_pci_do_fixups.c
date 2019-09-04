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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct pci_fixup {scalar_t__ class; int class_shift; scalar_t__ vendor; scalar_t__ device; void (* hook ) (struct pci_dev*) ;} ;
struct pci_dev {int class; scalar_t__ vendor; scalar_t__ device; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 scalar_t__ PCI_ANY_ID ; 
 int /*<<< orphan*/  fixup_debug_report (struct pci_dev*,int /*<<< orphan*/ ,void (*) (struct pci_dev*)) ; 
 int /*<<< orphan*/  fixup_debug_start (struct pci_dev*,void (*) (struct pci_dev*)) ; 

__attribute__((used)) static void pci_do_fixups(struct pci_dev *dev, struct pci_fixup *f,
			  struct pci_fixup *end)
{
	ktime_t calltime;

	for (; f < end; f++)
		if ((f->class == (u32) (dev->class >> f->class_shift) ||
		     f->class == (u32) PCI_ANY_ID) &&
		    (f->vendor == dev->vendor ||
		     f->vendor == (u16) PCI_ANY_ID) &&
		    (f->device == dev->device ||
		     f->device == (u16) PCI_ANY_ID)) {
			void (*hook)(struct pci_dev *dev);
#ifdef CONFIG_HAVE_ARCH_PREL32_RELOCATIONS
			hook = offset_to_ptr(&f->hook_offset);
#else
			hook = f->hook;
#endif
			calltime = fixup_debug_start(dev, hook);
			hook(dev);
			fixup_debug_report(dev, calltime, hook);
		}
}