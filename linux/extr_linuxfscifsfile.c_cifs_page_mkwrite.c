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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {struct page* page; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_FAULT_LOCKED ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 

__attribute__((used)) static vm_fault_t
cifs_page_mkwrite(struct vm_fault *vmf)
{
	struct page *page = vmf->page;

	lock_page(page);
	return VM_FAULT_LOCKED;
}