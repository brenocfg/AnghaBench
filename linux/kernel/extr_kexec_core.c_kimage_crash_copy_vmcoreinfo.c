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
struct page {int dummy; } ;
struct kimage {scalar_t__ type; void* vmcoreinfo_data_copy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ KEXEC_TYPE_CRASH ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int /*<<< orphan*/  VM_MAP ; 
 int /*<<< orphan*/  crash_update_vmcoreinfo_safecopy (void*) ; 
 struct page* kimage_alloc_control_pages (struct kimage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 void* vmap (struct page**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int kimage_crash_copy_vmcoreinfo(struct kimage *image)
{
	struct page *vmcoreinfo_page;
	void *safecopy;

	if (image->type != KEXEC_TYPE_CRASH)
		return 0;

	/*
	 * For kdump, allocate one vmcoreinfo safe copy from the
	 * crash memory. as we have arch_kexec_protect_crashkres()
	 * after kexec syscall, we naturally protect it from write
	 * (even read) access under kernel direct mapping. But on
	 * the other hand, we still need to operate it when crash
	 * happens to generate vmcoreinfo note, hereby we rely on
	 * vmap for this purpose.
	 */
	vmcoreinfo_page = kimage_alloc_control_pages(image, 0);
	if (!vmcoreinfo_page) {
		pr_warn("Could not allocate vmcoreinfo buffer\n");
		return -ENOMEM;
	}
	safecopy = vmap(&vmcoreinfo_page, 1, VM_MAP, PAGE_KERNEL);
	if (!safecopy) {
		pr_warn("Could not vmap vmcoreinfo buffer\n");
		return -ENOMEM;
	}

	image->vmcoreinfo_data_copy = safecopy;
	crash_update_vmcoreinfo_safecopy(safecopy);

	return 0;
}