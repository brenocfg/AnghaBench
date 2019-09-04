#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_gadget {int /*<<< orphan*/  dev; } ;
struct usb_composite_dev {struct usb_gadget* gadget; } ;
struct fsg_opts {int no_configfs; int /*<<< orphan*/  common; } ;
struct fsg_config {char* vendor_name; char* product_name; int /*<<< orphan*/  can_stall; } ;
struct TYPE_9__ {int iManufacturer; int iProduct; } ;
struct TYPE_8__ {int iConfiguration; } ;
struct TYPE_7__ {int id; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOKIA_LONG_NAME ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 size_t STRING_DESCRIPTION_IDX ; 
 size_t USB_GADGET_MANUFACTURER_IDX ; 
 size_t USB_GADGET_PRODUCT_IDX ; 
 int /*<<< orphan*/  coverwrite ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_6__ device_desc ; 
 int /*<<< orphan*/  f_acm_cfg1 ; 
 int /*<<< orphan*/  f_ecm_cfg1 ; 
 int /*<<< orphan*/  f_obex1_cfg1 ; 
 int /*<<< orphan*/  f_obex2_cfg1 ; 
 int /*<<< orphan*/  f_phonet_cfg1 ; 
 int /*<<< orphan*/  fi_acm ; 
 int /*<<< orphan*/  fi_ecm ; 
 int /*<<< orphan*/  fi_msg ; 
 int /*<<< orphan*/  fi_obex1 ; 
 int /*<<< orphan*/  fi_obex2 ; 
 int /*<<< orphan*/  fi_phonet ; 
 int fsg_common_create_luns (int /*<<< orphan*/ ,struct fsg_config*) ; 
 int /*<<< orphan*/  fsg_common_free_buffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsg_common_remove_luns (int /*<<< orphan*/ ) ; 
 int fsg_common_set_cdev (int /*<<< orphan*/ ,struct usb_composite_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsg_common_set_inquiry_string (int /*<<< orphan*/ ,char*,char*) ; 
 int fsg_common_set_num_buffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsg_common_set_sysfs (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsg_config_from_params (struct fsg_config*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsg_mod_data ; 
 int /*<<< orphan*/  fsg_num_buffers ; 
 struct fsg_opts* fsg_opts_from_func_inst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gadget_is_altset_supported (struct usb_gadget*) ; 
 int /*<<< orphan*/  nokia_bind_config ; 
 TYPE_2__ nokia_config_100ma_driver ; 
 TYPE_2__ nokia_config_500ma_driver ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 TYPE_1__* strings_dev ; 
 int usb_add_config (struct usb_composite_dev*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_composite_overwrite_options (struct usb_composite_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_get_function_instance (char*) ; 
 int /*<<< orphan*/  usb_put_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_function_instance (int /*<<< orphan*/ ) ; 
 int usb_string_ids_tab (struct usb_composite_dev*,TYPE_1__*) ; 

__attribute__((used)) static int nokia_bind(struct usb_composite_dev *cdev)
{
	struct usb_gadget	*gadget = cdev->gadget;
	struct fsg_opts		*fsg_opts;
	struct fsg_config	fsg_config;
	int			status;

	status = usb_string_ids_tab(cdev, strings_dev);
	if (status < 0)
		goto err_usb;
	device_desc.iManufacturer = strings_dev[USB_GADGET_MANUFACTURER_IDX].id;
	device_desc.iProduct = strings_dev[USB_GADGET_PRODUCT_IDX].id;
	status = strings_dev[STRING_DESCRIPTION_IDX].id;
	nokia_config_500ma_driver.iConfiguration = status;
	nokia_config_100ma_driver.iConfiguration = status;

	if (!gadget_is_altset_supported(gadget)) {
		status = -ENODEV;
		goto err_usb;
	}

	fi_phonet = usb_get_function_instance("phonet");
	if (IS_ERR(fi_phonet))
		pr_debug("could not find phonet function\n");

	fi_obex1 = usb_get_function_instance("obex");
	if (IS_ERR(fi_obex1))
		pr_debug("could not find obex function 1\n");

	fi_obex2 = usb_get_function_instance("obex");
	if (IS_ERR(fi_obex2))
		pr_debug("could not find obex function 2\n");

	fi_acm = usb_get_function_instance("acm");
	if (IS_ERR(fi_acm)) {
		status = PTR_ERR(fi_acm);
		goto err_obex2_inst;
	}

	fi_ecm = usb_get_function_instance("ecm");
	if (IS_ERR(fi_ecm)) {
		status = PTR_ERR(fi_ecm);
		goto err_acm_inst;
	}

	fi_msg = usb_get_function_instance("mass_storage");
	if (IS_ERR(fi_msg)) {
		status = PTR_ERR(fi_msg);
		goto err_ecm_inst;
	}

	/* set up mass storage function */
	fsg_config_from_params(&fsg_config, &fsg_mod_data, fsg_num_buffers);
	fsg_config.vendor_name = "Nokia";
	fsg_config.product_name = "N900";

	fsg_opts = fsg_opts_from_func_inst(fi_msg);
	fsg_opts->no_configfs = true;

	status = fsg_common_set_num_buffers(fsg_opts->common, fsg_num_buffers);
	if (status)
		goto err_msg_inst;

	status = fsg_common_set_cdev(fsg_opts->common, cdev, fsg_config.can_stall);
	if (status)
		goto err_msg_buf;

	fsg_common_set_sysfs(fsg_opts->common, true);

	status = fsg_common_create_luns(fsg_opts->common, &fsg_config);
	if (status)
		goto err_msg_buf;

	fsg_common_set_inquiry_string(fsg_opts->common, fsg_config.vendor_name,
				      fsg_config.product_name);

	/* finally register the configuration */
	status = usb_add_config(cdev, &nokia_config_500ma_driver,
			nokia_bind_config);
	if (status < 0)
		goto err_msg_luns;

	status = usb_add_config(cdev, &nokia_config_100ma_driver,
			nokia_bind_config);
	if (status < 0)
		goto err_put_cfg1;

	usb_composite_overwrite_options(cdev, &coverwrite);
	dev_info(&gadget->dev, "%s\n", NOKIA_LONG_NAME);

	return 0;

err_put_cfg1:
	usb_put_function(f_acm_cfg1);
	if (!IS_ERR_OR_NULL(f_obex1_cfg1))
		usb_put_function(f_obex1_cfg1);
	if (!IS_ERR_OR_NULL(f_obex2_cfg1))
		usb_put_function(f_obex2_cfg1);
	if (!IS_ERR_OR_NULL(f_phonet_cfg1))
		usb_put_function(f_phonet_cfg1);
	usb_put_function(f_ecm_cfg1);
err_msg_luns:
	fsg_common_remove_luns(fsg_opts->common);
err_msg_buf:
	fsg_common_free_buffers(fsg_opts->common);
err_msg_inst:
	usb_put_function_instance(fi_msg);
err_ecm_inst:
	usb_put_function_instance(fi_ecm);
err_acm_inst:
	usb_put_function_instance(fi_acm);
err_obex2_inst:
	if (!IS_ERR(fi_obex2))
		usb_put_function_instance(fi_obex2);
	if (!IS_ERR(fi_obex1))
		usb_put_function_instance(fi_obex1);
	if (!IS_ERR(fi_phonet))
		usb_put_function_instance(fi_phonet);
err_usb:
	return status;
}