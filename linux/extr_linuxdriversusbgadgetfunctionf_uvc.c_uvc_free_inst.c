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
struct usb_function_instance {int dummy; } ;
struct f_uvc_opts {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct f_uvc_opts* fi_to_f_uvc_opts (struct usb_function_instance*) ; 
 int /*<<< orphan*/  kfree (struct f_uvc_opts*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uvc_free_inst(struct usb_function_instance *f)
{
	struct f_uvc_opts *opts = fi_to_f_uvc_opts(f);

	mutex_destroy(&opts->lock);
	kfree(opts);
}