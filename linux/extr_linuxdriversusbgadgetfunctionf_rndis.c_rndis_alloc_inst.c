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
struct usb_os_desc {int /*<<< orphan*/  ext_prop; int /*<<< orphan*/  ext_compat_id; } ;
struct usb_function_instance {int /*<<< orphan*/  group; int /*<<< orphan*/  (* free_func_inst ) (struct usb_function_instance*) ;} ;
struct net_device {int dummy; } ;
struct f_rndis_opts {struct usb_function_instance func_inst; struct net_device* rndis_interf_group; struct usb_os_desc rndis_os_desc; int /*<<< orphan*/  protocol; int /*<<< orphan*/  subclass; int /*<<< orphan*/  class; struct net_device* net; int /*<<< orphan*/  lock; int /*<<< orphan*/  rndis_ext_compat_id; } ;
typedef  struct net_device config_group ;
struct TYPE_2__ {int /*<<< orphan*/  bFunctionProtocol; int /*<<< orphan*/  bFunctionSubClass; int /*<<< orphan*/  bFunctionClass; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct usb_function_instance* ERR_CAST (struct net_device*) ; 
 struct usb_function_instance* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 struct net_device* gether_setup_default () ; 
 int /*<<< orphan*/  kfree (struct f_rndis_opts*) ; 
 struct f_rndis_opts* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rndis_free_inst (struct usb_function_instance*) ; 
 int /*<<< orphan*/  rndis_func_type ; 
 TYPE_1__ rndis_iad_descriptor ; 
 struct net_device* usb_os_desc_prepare_interf_dir (int /*<<< orphan*/ *,int,struct usb_os_desc**,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct usb_function_instance *rndis_alloc_inst(void)
{
	struct f_rndis_opts *opts;
	struct usb_os_desc *descs[1];
	char *names[1];
	struct config_group *rndis_interf_group;

	opts = kzalloc(sizeof(*opts), GFP_KERNEL);
	if (!opts)
		return ERR_PTR(-ENOMEM);
	opts->rndis_os_desc.ext_compat_id = opts->rndis_ext_compat_id;

	mutex_init(&opts->lock);
	opts->func_inst.free_func_inst = rndis_free_inst;
	opts->net = gether_setup_default();
	if (IS_ERR(opts->net)) {
		struct net_device *net = opts->net;
		kfree(opts);
		return ERR_CAST(net);
	}
	INIT_LIST_HEAD(&opts->rndis_os_desc.ext_prop);

	opts->class = rndis_iad_descriptor.bFunctionClass;
	opts->subclass = rndis_iad_descriptor.bFunctionSubClass;
	opts->protocol = rndis_iad_descriptor.bFunctionProtocol;

	descs[0] = &opts->rndis_os_desc;
	names[0] = "rndis";
	config_group_init_type_name(&opts->func_inst.group, "",
				    &rndis_func_type);
	rndis_interf_group =
		usb_os_desc_prepare_interf_dir(&opts->func_inst.group, 1, descs,
					       names, THIS_MODULE);
	if (IS_ERR(rndis_interf_group)) {
		rndis_free_inst(&opts->func_inst);
		return ERR_CAST(rndis_interf_group);
	}
	opts->rndis_interf_group = rndis_interf_group;

	return &opts->func_inst;
}