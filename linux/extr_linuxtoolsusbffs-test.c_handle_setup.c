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
struct usb_ctrlrequest {int bRequestType; int bRequest; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void handle_setup(const struct usb_ctrlrequest *setup)
{
	printf("bRequestType = %d\n", setup->bRequestType);
	printf("bRequest     = %d\n", setup->bRequest);
	printf("wValue       = %d\n", le16_to_cpu(setup->wValue));
	printf("wIndex       = %d\n", le16_to_cpu(setup->wIndex));
	printf("wLength      = %d\n", le16_to_cpu(setup->wLength));
}