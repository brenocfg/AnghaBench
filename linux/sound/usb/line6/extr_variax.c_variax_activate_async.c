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
typedef  int /*<<< orphan*/  variax_activate ;
struct usb_line6_variax {int* buffer_activate; int /*<<< orphan*/  line6; } ;

/* Variables and functions */
 size_t VARIAX_OFFSET_ACTIVATE ; 
 int /*<<< orphan*/  line6_send_raw_message_async (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void variax_activate_async(struct usb_line6_variax *variax, int a)
{
	variax->buffer_activate[VARIAX_OFFSET_ACTIVATE] = a;
	line6_send_raw_message_async(&variax->line6, variax->buffer_activate,
				     sizeof(variax_activate));
}