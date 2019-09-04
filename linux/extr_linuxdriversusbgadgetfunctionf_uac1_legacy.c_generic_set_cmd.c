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
typedef  size_t u8 ;
struct usb_audio_control {int* data; } ;

/* Variables and functions */

__attribute__((used)) static int generic_set_cmd(struct usb_audio_control *con, u8 cmd, int value)
{
	con->data[cmd] = value;

	return 0;
}