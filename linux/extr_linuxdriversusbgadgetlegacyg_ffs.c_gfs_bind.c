#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_descriptor_header {int dummy; } ;
struct usb_composite_dev {int /*<<< orphan*/  gadget; } ;
struct TYPE_6__ {int bConfigurationValue; int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  iConfiguration; int /*<<< orphan*/  label; } ;
struct gfs_configuration {int num; TYPE_2__ c; } ;
struct TYPE_7__ {int /*<<< orphan*/  iProduct; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct gfs_configuration*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  USB_CONFIG_ATT_SELFPOWER ; 
 int USB_GADGET_FIRST_AVAIL_IDX ; 
 size_t USB_GADGET_PRODUCT_IDX ; 
 int /*<<< orphan*/  coverwrite ; 
 scalar_t__ gadget_is_otg (int /*<<< orphan*/ ) ; 
 struct gfs_configuration* gfs_configurations ; 
 TYPE_4__ gfs_dev_desc ; 
 int /*<<< orphan*/  gfs_do_config ; 
 struct usb_descriptor_header** gfs_otg_desc ; 
 TYPE_1__* gfs_strings ; 
 int /*<<< orphan*/  kfree (struct usb_descriptor_header*) ; 
 scalar_t__ missing_funcs ; 
 scalar_t__ unlikely (int) ; 
 int usb_add_config (struct usb_composite_dev*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_composite_overwrite_options (struct usb_composite_dev*,int /*<<< orphan*/ *) ; 
 struct usb_descriptor_header* usb_otg_descriptor_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_otg_descriptor_init (int /*<<< orphan*/ ,struct usb_descriptor_header*) ; 
 int usb_string_ids_tab (struct usb_composite_dev*,TYPE_1__*) ; 

__attribute__((used)) static int gfs_bind(struct usb_composite_dev *cdev)
{
#if defined CONFIG_USB_FUNCTIONFS_ETH || defined CONFIG_USB_FUNCTIONFS_RNDIS
	struct net_device *net;
#endif
	int ret, i;

	ENTER();

	if (missing_funcs)
		return -ENODEV;
#if defined CONFIG_USB_FUNCTIONFS_ETH
	if (can_support_ecm(cdev->gadget)) {
		struct f_ecm_opts *ecm_opts;

		fi_ecm = usb_get_function_instance("ecm");
		if (IS_ERR(fi_ecm))
			return PTR_ERR(fi_ecm);
		ecm_opts = container_of(fi_ecm, struct f_ecm_opts, func_inst);
		net = ecm_opts->net;
	} else {
		struct f_gether_opts *geth_opts;

		fi_geth = usb_get_function_instance("geth");
		if (IS_ERR(fi_geth))
			return PTR_ERR(fi_geth);
		geth_opts = container_of(fi_geth, struct f_gether_opts,
					 func_inst);
		net = geth_opts->net;
	}
#endif

#ifdef CONFIG_USB_FUNCTIONFS_RNDIS
	{
		fi_rndis = usb_get_function_instance("rndis");
		if (IS_ERR(fi_rndis)) {
			ret = PTR_ERR(fi_rndis);
			goto error;
		}
#ifndef CONFIG_USB_FUNCTIONFS_ETH
		net = container_of(fi_rndis, struct f_rndis_opts,
				   func_inst)->net;
#endif
	}
#endif

#if defined CONFIG_USB_FUNCTIONFS_ETH || defined CONFIG_USB_FUNCTIONFS_RNDIS
	gether_set_qmult(net, qmult);
	if (!gether_set_host_addr(net, host_addr))
		pr_info("using host ethernet address: %s", host_addr);
	if (!gether_set_dev_addr(net, dev_addr))
		pr_info("using self ethernet address: %s", dev_addr);
#endif

#if defined CONFIG_USB_FUNCTIONFS_RNDIS && defined CONFIG_USB_FUNCTIONFS_ETH
	gether_set_gadget(net, cdev->gadget);
	ret = gether_register_netdev(net);
	if (ret)
		goto error_rndis;

	if (can_support_ecm(cdev->gadget)) {
		struct f_ecm_opts *ecm_opts;

		ecm_opts = container_of(fi_ecm, struct f_ecm_opts, func_inst);
		ecm_opts->bound = true;
	} else {
		struct f_gether_opts *geth_opts;

		geth_opts = container_of(fi_geth, struct f_gether_opts,
					 func_inst);
		geth_opts->bound = true;
	}

	rndis_borrow_net(fi_rndis, net);
#endif

	/* TODO: gstrings_attach? */
	ret = usb_string_ids_tab(cdev, gfs_strings);
	if (unlikely(ret < 0))
		goto error_rndis;
	gfs_dev_desc.iProduct = gfs_strings[USB_GADGET_PRODUCT_IDX].id;

	if (gadget_is_otg(cdev->gadget) && !gfs_otg_desc[0]) {
		struct usb_descriptor_header *usb_desc;

		usb_desc = usb_otg_descriptor_alloc(cdev->gadget);
		if (!usb_desc)
			goto error_rndis;
		usb_otg_descriptor_init(cdev->gadget, usb_desc);
		gfs_otg_desc[0] = usb_desc;
		gfs_otg_desc[1] = NULL;
	}

	for (i = 0; i < ARRAY_SIZE(gfs_configurations); ++i) {
		struct gfs_configuration *c = gfs_configurations + i;
		int sid = USB_GADGET_FIRST_AVAIL_IDX + i;

		c->c.label			= gfs_strings[sid].s;
		c->c.iConfiguration		= gfs_strings[sid].id;
		c->c.bConfigurationValue	= 1 + i;
		c->c.bmAttributes		= USB_CONFIG_ATT_SELFPOWER;

		c->num = i;

		ret = usb_add_config(cdev, &c->c, gfs_do_config);
		if (unlikely(ret < 0))
			goto error_unbind;
	}
	usb_composite_overwrite_options(cdev, &coverwrite);
	return 0;

/* TODO */
error_unbind:
	kfree(gfs_otg_desc[0]);
	gfs_otg_desc[0] = NULL;
error_rndis:
#ifdef CONFIG_USB_FUNCTIONFS_RNDIS
	usb_put_function_instance(fi_rndis);
error:
#endif
#if defined CONFIG_USB_FUNCTIONFS_ETH
	if (can_support_ecm(cdev->gadget))
		usb_put_function_instance(fi_ecm);
	else
		usb_put_function_instance(fi_geth);
#endif
	return ret;
}