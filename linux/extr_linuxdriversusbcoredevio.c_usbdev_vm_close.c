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
struct vm_area_struct {struct usb_memory* vm_private_data; } ;
struct usb_memory {int /*<<< orphan*/  vma_use_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  dec_usb_memory_use_count (struct usb_memory*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usbdev_vm_close(struct vm_area_struct *vma)
{
	struct usb_memory *usbm = vma->vm_private_data;

	dec_usb_memory_use_count(usbm, &usbm->vma_use_count);
}