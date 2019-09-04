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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct usbnet {int dummy; } ;

/* Variables and functions */
 int __usbnet_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 

int usbnet_write_cmd_nopm(struct usbnet *dev, u8 cmd, u8 reqtype,
			  u16 value, u16 index, const void *data,
			  u16 size)
{
	return __usbnet_write_cmd(dev, cmd, reqtype, value, index,
				  data, size);
}