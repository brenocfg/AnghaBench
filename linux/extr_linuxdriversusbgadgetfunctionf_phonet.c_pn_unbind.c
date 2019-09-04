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
struct usb_function {int dummy; } ;
struct usb_configuration {int dummy; } ;
struct f_phonet {scalar_t__* out_reqv; int /*<<< orphan*/  out_ep; scalar_t__ in_req; int /*<<< orphan*/  in_ep; } ;

/* Variables and functions */
 struct f_phonet* func_to_pn (struct usb_function*) ; 
 int phonet_rxq_size ; 
 int /*<<< orphan*/  usb_ep_free_request (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usb_free_all_descriptors (struct usb_function*) ; 

__attribute__((used)) static void pn_unbind(struct usb_configuration *c, struct usb_function *f)
{
	struct f_phonet *fp = func_to_pn(f);
	int i;

	/* We are already disconnected */
	if (fp->in_req)
		usb_ep_free_request(fp->in_ep, fp->in_req);
	for (i = 0; i < phonet_rxq_size; i++)
		if (fp->out_reqv[i])
			usb_ep_free_request(fp->out_ep, fp->out_reqv[i]);

	usb_free_all_descriptors(f);
}