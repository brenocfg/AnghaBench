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
struct musb {int /*<<< orphan*/  xceiv; int /*<<< orphan*/  nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_put_phy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ux500_musb_exit(struct musb *musb)
{
	usb_unregister_notifier(musb->xceiv, &musb->nb);

	usb_put_phy(musb->xceiv);

	return 0;
}