#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {unsigned long pgoff; struct page* page; TYPE_1__* vma; } ;
struct usb_stream {int /*<<< orphan*/  write_size; int /*<<< orphan*/  read_size; } ;
struct TYPE_4__ {void* write_page; struct usb_stream* s; } ;
struct us122l {int /*<<< orphan*/  mutex; TYPE_2__ sk; } ;
struct page {int dummy; } ;
struct TYPE_3__ {struct us122l* vm_private_data; } ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct page* virt_to_page (void*) ; 

__attribute__((used)) static vm_fault_t usb_stream_hwdep_vm_fault(struct vm_fault *vmf)
{
	unsigned long offset;
	struct page *page;
	void *vaddr;
	struct us122l *us122l = vmf->vma->vm_private_data;
	struct usb_stream *s;

	mutex_lock(&us122l->mutex);
	s = us122l->sk.s;
	if (!s)
		goto unlock;

	offset = vmf->pgoff << PAGE_SHIFT;
	if (offset < PAGE_ALIGN(s->read_size))
		vaddr = (char *)s + offset;
	else {
		offset -= PAGE_ALIGN(s->read_size);
		if (offset >= PAGE_ALIGN(s->write_size))
			goto unlock;

		vaddr = us122l->sk.write_page + offset;
	}
	page = virt_to_page(vaddr);

	get_page(page);
	mutex_unlock(&us122l->mutex);

	vmf->page = page;

	return 0;
unlock:
	mutex_unlock(&us122l->mutex);
	return VM_FAULT_SIGBUS;
}