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
struct usb_function_instance {int /*<<< orphan*/  group; int /*<<< orphan*/  free_func_inst; } ;
struct f_serial_opts {struct usb_function_instance func_inst; int /*<<< orphan*/  port_num; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct usb_function_instance* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gser_free_inst ; 
 int gserial_alloc_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct f_serial_opts*) ; 
 struct f_serial_opts* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_func_type ; 

__attribute__((used)) static struct usb_function_instance *gser_alloc_inst(void)
{
	struct f_serial_opts *opts;
	int ret;

	opts = kzalloc(sizeof(*opts), GFP_KERNEL);
	if (!opts)
		return ERR_PTR(-ENOMEM);

	opts->func_inst.free_func_inst = gser_free_inst;
	ret = gserial_alloc_line(&opts->port_num);
	if (ret) {
		kfree(opts);
		return ERR_PTR(ret);
	}
	config_group_init_type_name(&opts->func_inst.group, "",
				    &serial_func_type);

	return &opts->func_inst;
}