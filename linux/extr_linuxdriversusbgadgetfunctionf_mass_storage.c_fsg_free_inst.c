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
struct fsg_opts {int /*<<< orphan*/  common; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsg_common_release (int /*<<< orphan*/ ) ; 
 struct fsg_opts* fsg_opts_from_func_inst (struct usb_function_instance*) ; 
 int /*<<< orphan*/  kfree (struct fsg_opts*) ; 

__attribute__((used)) static void fsg_free_inst(struct usb_function_instance *fi)
{
	struct fsg_opts *opts;

	opts = fsg_opts_from_func_inst(fi);
	fsg_common_release(opts->common);
	kfree(opts);
}