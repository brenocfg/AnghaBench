#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ wLength; int bRequest; } ;
struct TYPE_4__ {TYPE_1__ req; } ;

/* Variables and functions */
#define  USB_REQ_CLEAR_FEATURE 137 
#define  USB_REQ_GET_CONFIGURATION 136 
#define  USB_REQ_GET_DESCRIPTOR 135 
#define  USB_REQ_GET_INTERFACE 134 
#define  USB_REQ_GET_STATUS 133 
 scalar_t__ USB_REQ_RECIP_DEVICE ; 
 scalar_t__ USB_REQ_RECIP_ENDPOINT ; 
 scalar_t__ USB_REQ_RECIP_INTERFACE ; 
#define  USB_REQ_SET_ADDRESS 132 
#define  USB_REQ_SET_CONFIGURATION 131 
#define  USB_REQ_SET_DESCRIPTOR 130 
#define  USB_REQ_SET_FEATURE 129 
#define  USB_REQ_SET_INTERFACE 128 
 scalar_t__ Udd_setup_is_in () ; 
 scalar_t__ Udd_setup_recipient () ; 
 int udc_req_std_dev_clear_feature () ; 
 int udc_req_std_dev_get_configuration () ; 
 int udc_req_std_dev_get_descriptor () ; 
 int udc_req_std_dev_get_status () ; 
 int udc_req_std_dev_set_address () ; 
 int udc_req_std_dev_set_configuration () ; 
 int udc_req_std_dev_set_feature () ; 
 int udc_req_std_ep_clear_feature () ; 
 int udc_req_std_ep_get_status () ; 
 int udc_req_std_ep_set_feature () ; 
 int udc_req_std_iface_get_setting () ; 
 int udc_req_std_iface_set_setting () ; 
 TYPE_2__ udd_g_ctrlreq ; 

__attribute__((used)) static bool udc_reqstd(void) {
    if (Udd_setup_is_in()) {
        // GET Standard Requests
        if (udd_g_ctrlreq.req.wLength == 0) {
            return false;  // Error for USB host
        }

        if (USB_REQ_RECIP_DEVICE == Udd_setup_recipient()) {
            // Standard Get Device request
            switch (udd_g_ctrlreq.req.bRequest) {
                case USB_REQ_GET_STATUS:
                    return udc_req_std_dev_get_status();
                case USB_REQ_GET_DESCRIPTOR:
                    return udc_req_std_dev_get_descriptor();
                case USB_REQ_GET_CONFIGURATION:
                    return udc_req_std_dev_get_configuration();
                default:
                    break;
            }
        }

        if (USB_REQ_RECIP_INTERFACE == Udd_setup_recipient()) {
            // Standard Get Interface request
            switch (udd_g_ctrlreq.req.bRequest) {
                case USB_REQ_GET_INTERFACE:
                    return udc_req_std_iface_get_setting();
                default:
                    break;
            }
        }
#if (0 != USB_DEVICE_MAX_EP)
        if (USB_REQ_RECIP_ENDPOINT == Udd_setup_recipient()) {
            // Standard Get Endpoint request
            switch (udd_g_ctrlreq.req.bRequest) {
                case USB_REQ_GET_STATUS:
                    return udc_req_std_ep_get_status();
                default:
                    break;
            }
        }
#endif
    } else {
        // SET Standard Requests
        if (USB_REQ_RECIP_DEVICE == Udd_setup_recipient()) {
            // Standard Set Device request
            switch (udd_g_ctrlreq.req.bRequest) {
                case USB_REQ_SET_ADDRESS:
                    return udc_req_std_dev_set_address();
                case USB_REQ_CLEAR_FEATURE:
                    return udc_req_std_dev_clear_feature();
                case USB_REQ_SET_FEATURE:
                    return udc_req_std_dev_set_feature();
                case USB_REQ_SET_CONFIGURATION:
                    return udc_req_std_dev_set_configuration();
                case USB_REQ_SET_DESCRIPTOR:
                    /* Not supported (defined as optional by the USB 2.0 spec) */
                    break;
                default:
                    break;
            }
        }

        if (USB_REQ_RECIP_INTERFACE == Udd_setup_recipient()) {
            // Standard Set Interface request
            switch (udd_g_ctrlreq.req.bRequest) {
                case USB_REQ_SET_INTERFACE:
                    return udc_req_std_iface_set_setting();
                default:
                    break;
            }
        }
#if (0 != USB_DEVICE_MAX_EP)
        if (USB_REQ_RECIP_ENDPOINT == Udd_setup_recipient()) {
            // Standard Set Endpoint request
            switch (udd_g_ctrlreq.req.bRequest) {
                case USB_REQ_CLEAR_FEATURE:
                    return udc_req_std_ep_clear_feature();
                case USB_REQ_SET_FEATURE:
                    return udc_req_std_ep_set_feature();
                default:
                    break;
            }
        }
#endif
    }
    return false;
}