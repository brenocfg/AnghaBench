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
struct usbip_iso_packet_descriptor {int dummy; } ;
struct urb {int number_of_packets; int /*<<< orphan*/ * iso_frame_desc; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct usbip_iso_packet_descriptor* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_iso_packet_correct_endian (struct usbip_iso_packet_descriptor*,int) ; 
 int /*<<< orphan*/  usbip_pack_iso (struct usbip_iso_packet_descriptor*,int /*<<< orphan*/ *,int) ; 

struct usbip_iso_packet_descriptor*
usbip_alloc_iso_desc_pdu(struct urb *urb, ssize_t *bufflen)
{
	struct usbip_iso_packet_descriptor *iso;
	int np = urb->number_of_packets;
	ssize_t size = np * sizeof(*iso);
	int i;

	iso = kzalloc(size, GFP_KERNEL);
	if (!iso)
		return NULL;

	for (i = 0; i < np; i++) {
		usbip_pack_iso(&iso[i], &urb->iso_frame_desc[i], 1);
		usbip_iso_packet_correct_endian(&iso[i], 1);
	}

	*bufflen = size;

	return iso;
}