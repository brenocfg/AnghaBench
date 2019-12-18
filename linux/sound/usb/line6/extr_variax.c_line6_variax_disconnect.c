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
struct usb_line6_variax {int /*<<< orphan*/  buffer_activate; } ;
struct usb_line6 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct usb_line6_variax* line6_to_variax (struct usb_line6*) ; 

__attribute__((used)) static void line6_variax_disconnect(struct usb_line6 *line6)
{
	struct usb_line6_variax *variax = line6_to_variax(line6);

	kfree(variax->buffer_activate);
}