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
typedef  int uint32_t ;
struct usb_module {int dummy; } ;
struct usb_device_endpoint_config {int ep_size; } ;
typedef  enum usb_endpoint_size { ____Placeholder_usb_endpoint_size } usb_endpoint_size ;

/* Variables and functions */
 int /*<<< orphan*/  Max (int /*<<< orphan*/ ,int) ; 
 scalar_t__ Min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UDD_EPCTRL_SETUP ; 
 int /*<<< orphan*/  USB_DEVICE_ENDPOINT_CALLBACK_RXSTP ; 
 int /*<<< orphan*/  USB_DEVICE_ENDPOINT_CALLBACK_TRCPT ; 
 int /*<<< orphan*/  USB_DEVICE_ENDPOINT_CALLBACK_TRFAIL ; 
 int /*<<< orphan*/  USB_DEVICE_EP_CTRL_SIZE ; 
 int /*<<< orphan*/  USB_DEVICE_LPM_ACK ; 
 int /*<<< orphan*/  _usb_ep0_on_setup ; 
 int /*<<< orphan*/  _usb_ep0_on_tansfer_fail ; 
 int /*<<< orphan*/  _usb_ep0_on_tansfer_ok ; 
 int clz (int) ; 
 int /*<<< orphan*/  udd_ctrl_buffer ; 
 int /*<<< orphan*/  udd_ep_control_state ; 
 int /*<<< orphan*/  usb_device_endpoint_enable_callback (struct usb_module*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_device_endpoint_get_config_defaults (struct usb_device_endpoint_config*) ; 
 int /*<<< orphan*/  usb_device_endpoint_register_callback (struct usb_module*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_device_endpoint_set_config (struct usb_module*,struct usb_device_endpoint_config*) ; 
 int /*<<< orphan*/  usb_device_endpoint_setup_buffer_job (struct usb_module*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_device_set_lpm_mode (struct usb_module*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udd_ctrl_ep_enable(struct usb_module *module_inst) {
    /* USB Device Endpoint0 Configuration */
    struct usb_device_endpoint_config config_ep0;

    usb_device_endpoint_get_config_defaults(&config_ep0);
    config_ep0.ep_size = (enum usb_endpoint_size)(32 - clz(((uint32_t)Min(Max(USB_DEVICE_EP_CTRL_SIZE, 8), 1024) << 1) - 1) - 1 - 3);
    usb_device_endpoint_set_config(module_inst, &config_ep0);

    usb_device_endpoint_setup_buffer_job(module_inst, udd_ctrl_buffer);

    usb_device_endpoint_register_callback(module_inst, 0, USB_DEVICE_ENDPOINT_CALLBACK_RXSTP, _usb_ep0_on_setup);
    usb_device_endpoint_register_callback(module_inst, 0, USB_DEVICE_ENDPOINT_CALLBACK_TRCPT, _usb_ep0_on_tansfer_ok);
    usb_device_endpoint_register_callback(module_inst, 0, USB_DEVICE_ENDPOINT_CALLBACK_TRFAIL, _usb_ep0_on_tansfer_fail);
    usb_device_endpoint_enable_callback(module_inst, 0, USB_DEVICE_ENDPOINT_CALLBACK_RXSTP);
    usb_device_endpoint_enable_callback(module_inst, 0, USB_DEVICE_ENDPOINT_CALLBACK_TRCPT);
    usb_device_endpoint_enable_callback(module_inst, 0, USB_DEVICE_ENDPOINT_CALLBACK_TRFAIL);

#ifdef USB_DEVICE_LPM_SUPPORT
    // Enable LPM feature
    usb_device_set_lpm_mode(module_inst, USB_DEVICE_LPM_ACK);
#endif

    udd_ep_control_state = UDD_EPCTRL_SETUP;
}