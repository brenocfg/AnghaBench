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
struct f_lb_opts {struct usb_function_instance func_inst; int /*<<< orphan*/  qlen; int /*<<< orphan*/  bulk_buflen; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct usb_function_instance* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GZERO_BULK_BUFLEN ; 
 int /*<<< orphan*/  GZERO_QLEN ; 
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 struct f_lb_opts* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lb_free_instance ; 
 int /*<<< orphan*/  lb_func_type ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct usb_function_instance *loopback_alloc_instance(void)
{
	struct f_lb_opts *lb_opts;

	lb_opts = kzalloc(sizeof(*lb_opts), GFP_KERNEL);
	if (!lb_opts)
		return ERR_PTR(-ENOMEM);
	mutex_init(&lb_opts->lock);
	lb_opts->func_inst.free_func_inst = lb_free_instance;
	lb_opts->bulk_buflen = GZERO_BULK_BUFLEN;
	lb_opts->qlen = GZERO_QLEN;

	config_group_init_type_name(&lb_opts->func_inst.group, "",
				    &lb_func_type);

	return  &lb_opts->func_inst;
}