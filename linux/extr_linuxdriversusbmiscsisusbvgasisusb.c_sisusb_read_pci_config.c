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
typedef  int u32 ;
struct sisusb_usb_data {int dummy; } ;
struct sisusb_packet {int header; int address; int data; } ;

/* Variables and functions */
 int sisusb_send_packet (struct sisusb_usb_data*,int,struct sisusb_packet*) ; 

__attribute__((used)) static int sisusb_read_pci_config(struct sisusb_usb_data *sisusb,
		int regnum, u32 *data)
{
	struct sisusb_packet packet;
	int ret;

	packet.header = 0x008f;
	packet.address = (u32)regnum | 0x10000;
	ret = sisusb_send_packet(sisusb, 6, &packet);
	*data = packet.data;
	return ret;
}