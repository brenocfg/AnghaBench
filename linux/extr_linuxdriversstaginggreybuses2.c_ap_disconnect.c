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
struct usb_interface {int dummy; } ;
struct es2_ap_dev {int /*<<< orphan*/  cport_in; int /*<<< orphan*/  hd; } ;

/* Variables and functions */
 int /*<<< orphan*/  es2_arpc_in_disable (struct es2_ap_dev*) ; 
 int /*<<< orphan*/  es2_cport_in_disable (struct es2_ap_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es2_destroy (struct es2_ap_dev*) ; 
 int /*<<< orphan*/  gb_hd_del (int /*<<< orphan*/ ) ; 
 struct es2_ap_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void ap_disconnect(struct usb_interface *interface)
{
	struct es2_ap_dev *es2 = usb_get_intfdata(interface);

	gb_hd_del(es2->hd);

	es2_cport_in_disable(es2, &es2->cport_in);
	es2_arpc_in_disable(es2);

	es2_destroy(es2);
}