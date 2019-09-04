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
struct pcm_urb {int /*<<< orphan*/  submitted; int /*<<< orphan*/  instance; scalar_t__ buffer; struct hiface_chip* chip; } ;
struct hiface_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCM_PACKET_SIZE ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 scalar_t__ kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void (*) (struct urb*),struct pcm_urb*) ; 
 int /*<<< orphan*/  usb_init_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ usb_urb_ep_type_check (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hiface_pcm_init_urb(struct pcm_urb *urb,
			       struct hiface_chip *chip,
			       unsigned int ep,
			       void (*handler)(struct urb *))
{
	urb->chip = chip;
	usb_init_urb(&urb->instance);

	urb->buffer = kzalloc(PCM_PACKET_SIZE, GFP_KERNEL);
	if (!urb->buffer)
		return -ENOMEM;

	usb_fill_bulk_urb(&urb->instance, chip->dev,
			  usb_sndbulkpipe(chip->dev, ep), (void *)urb->buffer,
			  PCM_PACKET_SIZE, handler, urb);
	if (usb_urb_ep_type_check(&urb->instance))
		return -EINVAL;
	init_usb_anchor(&urb->submitted);

	return 0;
}