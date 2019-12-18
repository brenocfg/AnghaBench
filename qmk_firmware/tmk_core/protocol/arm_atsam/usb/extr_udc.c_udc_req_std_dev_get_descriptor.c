#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {int bDescriptorType; } ;
typedef  TYPE_10__ usb_conf_desc_t ;
typedef  size_t uint8_t ;
struct TYPE_24__ {int wValue; scalar_t__ wLength; } ;
struct TYPE_23__ {int /*<<< orphan*/  wTotalLength; } ;
struct TYPE_22__ {TYPE_6__* desc; } ;
struct TYPE_21__ {int /*<<< orphan*/  wTotalLength; } ;
struct TYPE_20__ {size_t bNumConfigurations; int /*<<< orphan*/  bLength; } ;
struct TYPE_19__ {TYPE_3__* desc; } ;
struct TYPE_18__ {int /*<<< orphan*/  wTotalLength; } ;
struct TYPE_17__ {size_t bNumConfigurations; int /*<<< orphan*/  bLength; } ;
struct TYPE_16__ {int /*<<< orphan*/  bLength; } ;
struct TYPE_15__ {TYPE_8__* conf_bos; TYPE_7__* conf_lsfs; TYPE_5__* confdev_lsfs; TYPE_4__* conf_hs; TYPE_2__* confdev_hs; TYPE_1__* qualifier; } ;
struct TYPE_14__ {scalar_t__ payload_size; TYPE_9__ req; scalar_t__ payload; } ;

/* Variables and functions */
#define  USB_DT_BOS 133 
#define  USB_DT_CONFIGURATION 132 
#define  USB_DT_DEVICE 131 
#define  USB_DT_DEVICE_QUALIFIER 130 
#define  USB_DT_OTHER_SPEED_CONFIGURATION 129 
#define  USB_DT_STRING 128 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_12__ udc_config ; 
 int /*<<< orphan*/  udc_req_std_dev_get_str_desc () ; 
 TYPE_11__ udd_g_ctrlreq ; 
 int /*<<< orphan*/  udd_is_high_speed () ; 
 int /*<<< orphan*/  udd_set_setup_payload (size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool udc_req_std_dev_get_descriptor(void) {
    uint8_t conf_num;

    conf_num = udd_g_ctrlreq.req.wValue & 0xff;

    // Check descriptor ID
    switch ((uint8_t)(udd_g_ctrlreq.req.wValue >> 8)) {
        case USB_DT_DEVICE:
            // Device descriptor requested
#ifdef USB_DEVICE_HS_SUPPORT
            if (!udd_is_high_speed()) {
                udd_set_setup_payload((uint8_t *)udc_config.confdev_hs, udc_config.confdev_hs->bLength);
            } else
#endif
            {
                udd_set_setup_payload((uint8_t *)udc_config.confdev_lsfs, udc_config.confdev_lsfs->bLength);
            }
            break;

        case USB_DT_CONFIGURATION:
            // Configuration descriptor requested
#ifdef USB_DEVICE_HS_SUPPORT
            if (udd_is_high_speed()) {
                // HS descriptor
                if (conf_num >= udc_config.confdev_hs->bNumConfigurations) {
                    return false;
                }
                udd_set_setup_payload((uint8_t *)udc_config.conf_hs[conf_num].desc, le16_to_cpu(udc_config.conf_hs[conf_num].desc->wTotalLength));
            } else
#endif
            {
                // FS descriptor
                if (conf_num >= udc_config.confdev_lsfs->bNumConfigurations) {
                    return false;
                }
                udd_set_setup_payload((uint8_t *)udc_config.conf_lsfs[conf_num].desc, le16_to_cpu(udc_config.conf_lsfs[conf_num].desc->wTotalLength));
            }
            ((usb_conf_desc_t *)udd_g_ctrlreq.payload)->bDescriptorType = USB_DT_CONFIGURATION;
            break;

#ifdef USB_DEVICE_HS_SUPPORT
        case USB_DT_DEVICE_QUALIFIER:
            // Device qualifier descriptor requested
            udd_set_setup_payload((uint8_t *)udc_config.qualifier, udc_config.qualifier->bLength);
            break;

        case USB_DT_OTHER_SPEED_CONFIGURATION:
            // Other configuration descriptor requested
            if (!udd_is_high_speed()) {
                // HS descriptor
                if (conf_num >= udc_config.confdev_hs->bNumConfigurations) {
                    return false;
                }
                udd_set_setup_payload((uint8_t *)udc_config.conf_hs[conf_num].desc, le16_to_cpu(udc_config.conf_hs[conf_num].desc->wTotalLength));
            } else {
                // FS descriptor
                if (conf_num >= udc_config.confdev_lsfs->bNumConfigurations) {
                    return false;
                }
                udd_set_setup_payload((uint8_t *)udc_config.conf_lsfs[conf_num].desc, le16_to_cpu(udc_config.conf_lsfs[conf_num].desc->wTotalLength));
            }
            ((usb_conf_desc_t *)udd_g_ctrlreq.payload)->bDescriptorType = USB_DT_OTHER_SPEED_CONFIGURATION;
            break;
#endif

        case USB_DT_BOS:
            // Device BOS descriptor requested
            if (udc_config.conf_bos == NULL) {
                return false;
            }
            udd_set_setup_payload((uint8_t *)udc_config.conf_bos, udc_config.conf_bos->wTotalLength);
            break;

        case USB_DT_STRING:
            // String descriptor requested
            if (!udc_req_std_dev_get_str_desc()) {
                return false;
            }
            break;

        default:
            // Unknown descriptor requested
            return false;
    }
    // if the descriptor is larger than length requested, then reduce it
    if (udd_g_ctrlreq.req.wLength < udd_g_ctrlreq.payload_size) {
        udd_g_ctrlreq.payload_size = udd_g_ctrlreq.req.wLength;
    }
    return true;
}