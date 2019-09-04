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
typedef  int /*<<< orphan*/  u32 ;
struct sisusb_usb_data {int dummy; } ;
struct sisusb_packet {int header; int address; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int sisusb_send_packet (struct sisusb_usb_data*,int,struct sisusb_packet*) ; 

__attribute__((used)) static int sisusb_write_pci_config(struct sisusb_usb_data *sisusb,
		int regnum, u32 data)
{
	struct sisusb_packet packet;

	packet.header = 0x008f;
	packet.address = regnum | 0x10000;
	packet.data = data;
	return sisusb_send_packet(sisusb, 10, &packet);
}