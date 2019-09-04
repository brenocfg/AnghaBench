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
struct f_lb_opts {int /*<<< orphan*/  func_inst; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 struct f_lb_opts* to_f_lb_opts (struct config_item*) ; 
 int /*<<< orphan*/  usb_put_function_instance (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lb_attr_release(struct config_item *item)
{
	struct f_lb_opts *lb_opts = to_f_lb_opts(item);

	usb_put_function_instance(&lb_opts->func_inst);
}