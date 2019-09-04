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
struct usb_gadget {int dummy; } ;
struct musb {int /*<<< orphan*/  mregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_FRAME ; 
 struct musb* gadget_to_musb (struct usb_gadget*) ; 
 scalar_t__ musb_readw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int musb_gadget_get_frame(struct usb_gadget *gadget)
{
	struct musb	*musb = gadget_to_musb(gadget);

	return (int)musb_readw(musb->mregs, MUSB_FRAME);
}