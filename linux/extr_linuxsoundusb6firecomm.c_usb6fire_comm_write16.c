#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct comm_runtime {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb6fire_comm_init_buffer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb6fire_comm_send_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb6fire_comm_write16(struct comm_runtime *rt, u8 request,
		u8 reg, u8 vl, u8 vh)
{
	u8 *buffer;
	int ret;

	/* 13: maximum length of message */
	buffer = kmalloc(13, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	usb6fire_comm_init_buffer(buffer, 0x00, request, reg, vl, vh);
	ret = usb6fire_comm_send_buffer(buffer, rt->chip->dev);

	kfree(buffer);
	return ret;
}