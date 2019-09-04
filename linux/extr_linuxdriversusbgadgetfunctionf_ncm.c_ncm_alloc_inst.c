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
struct net_device {int dummy; } ;
struct f_ncm_opts {struct usb_function_instance func_inst; struct net_device* net; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct usb_function_instance* ERR_CAST (struct net_device*) ; 
 struct usb_function_instance* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 struct net_device* gether_setup_default () ; 
 int /*<<< orphan*/  kfree (struct f_ncm_opts*) ; 
 struct f_ncm_opts* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncm_free_inst ; 
 int /*<<< orphan*/  ncm_func_type ; 

__attribute__((used)) static struct usb_function_instance *ncm_alloc_inst(void)
{
	struct f_ncm_opts *opts;

	opts = kzalloc(sizeof(*opts), GFP_KERNEL);
	if (!opts)
		return ERR_PTR(-ENOMEM);
	mutex_init(&opts->lock);
	opts->func_inst.free_func_inst = ncm_free_inst;
	opts->net = gether_setup_default();
	if (IS_ERR(opts->net)) {
		struct net_device *net = opts->net;
		kfree(opts);
		return ERR_CAST(net);
	}

	config_group_init_type_name(&opts->func_inst.group, "", &ncm_func_type);

	return &opts->func_inst;
}