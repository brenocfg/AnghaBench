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
struct usb_request {int dummy; } ;
struct usb_function {TYPE_1__* config; } ;
struct usb_composite_dev {int dummy; } ;
struct f_midi {int /*<<< orphan*/  in_ep; int /*<<< orphan*/  in_req_fifo; int /*<<< orphan*/  out_ep; } ;
struct TYPE_2__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*) ; 
 int /*<<< orphan*/  f_midi_drop_out_substreams (struct f_midi*) ; 
 int /*<<< orphan*/  free_ep_req (int /*<<< orphan*/ ,struct usb_request*) ; 
 struct f_midi* func_to_midi (struct usb_function*) ; 
 scalar_t__ kfifo_get (int /*<<< orphan*/ *,struct usb_request**) ; 
 int /*<<< orphan*/  usb_ep_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void f_midi_disable(struct usb_function *f)
{
	struct f_midi *midi = func_to_midi(f);
	struct usb_composite_dev *cdev = f->config->cdev;
	struct usb_request *req = NULL;

	DBG(cdev, "disable\n");

	/*
	 * just disable endpoints, forcing completion of pending i/o.
	 * all our completion handlers free their requests in this case.
	 */
	usb_ep_disable(midi->in_ep);
	usb_ep_disable(midi->out_ep);

	/* release IN requests */
	while (kfifo_get(&midi->in_req_fifo, &req))
		free_ep_req(midi->in_ep, req);

	f_midi_drop_out_substreams(midi);
}