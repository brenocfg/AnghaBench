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
struct usb_function {int /*<<< orphan*/  ssp_descriptors; int /*<<< orphan*/  ss_descriptors; int /*<<< orphan*/  hs_descriptors; int /*<<< orphan*/  fs_descriptors; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_free_descriptors (int /*<<< orphan*/ ) ; 

void usb_free_all_descriptors(struct usb_function *f)
{
	usb_free_descriptors(f->fs_descriptors);
	usb_free_descriptors(f->hs_descriptors);
	usb_free_descriptors(f->ss_descriptors);
	usb_free_descriptors(f->ssp_descriptors);
}