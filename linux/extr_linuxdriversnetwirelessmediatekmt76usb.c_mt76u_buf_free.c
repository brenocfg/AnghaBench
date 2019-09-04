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
struct urb {int num_sgs; int /*<<< orphan*/ * sg; } ;
struct mt76u_buf {struct urb* urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_virt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_free_frag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

void mt76u_buf_free(struct mt76u_buf *buf)
{
	struct urb *urb = buf->urb;
	int i;

	for (i = 0; i < urb->num_sgs; i++)
		skb_free_frag(sg_virt(&urb->sg[i]));
	usb_free_urb(buf->urb);
}