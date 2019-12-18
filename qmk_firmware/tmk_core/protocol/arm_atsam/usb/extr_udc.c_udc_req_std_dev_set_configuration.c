#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_14__ {TYPE_6__* conf_lsfs; TYPE_6__* conf_hs; TYPE_2__* confdev_lsfs; TYPE_1__* confdev_hs; } ;
struct TYPE_13__ {TYPE_3__* desc; } ;
struct TYPE_11__ {int wValue; scalar_t__ wLength; } ;
struct TYPE_12__ {TYPE_4__ req; } ;
struct TYPE_10__ {scalar_t__ bNumInterfaces; } ;
struct TYPE_9__ {int bNumConfigurations; } ;
struct TYPE_8__ {int bNumConfigurations; } ;

/* Variables and functions */
 TYPE_7__ udc_config ; 
 int /*<<< orphan*/  udc_iface_enable (scalar_t__,int /*<<< orphan*/ ) ; 
 int udc_num_configuration ; 
 TYPE_6__* udc_ptr_conf ; 
 int /*<<< orphan*/  udc_reset () ; 
 TYPE_5__ udd_g_ctrlreq ; 
 int /*<<< orphan*/  udd_getaddress () ; 
 scalar_t__ udd_is_high_speed () ; 

__attribute__((used)) static bool udc_req_std_dev_set_configuration(void) {
    uint8_t iface_num;

    // Check request length
    if (udd_g_ctrlreq.req.wLength) {
        return false;
    }
    // Authorize configuration only if the address is valid
    if (!udd_getaddress()) {
        return false;
    }
    // Check the configuration number requested
#ifdef USB_DEVICE_HS_SUPPORT
    if (udd_is_high_speed()) {
        // HS descriptor
        if ((udd_g_ctrlreq.req.wValue & 0xFF) > udc_config.confdev_hs->bNumConfigurations) {
            return false;
        }
    } else
#endif
    {
        // FS descriptor
        if ((udd_g_ctrlreq.req.wValue & 0xFF) > udc_config.confdev_lsfs->bNumConfigurations) {
            return false;
        }
    }

    // Reset current configuration
    udc_reset();

    // Enable new configuration
    udc_num_configuration = udd_g_ctrlreq.req.wValue & 0xFF;
    if (udc_num_configuration == 0) {
        return true;  // Default empty configuration requested
    }
    // Update pointer of the configuration descriptor
#ifdef USB_DEVICE_HS_SUPPORT
    if (udd_is_high_speed()) {
        // HS descriptor
        udc_ptr_conf = &udc_config.conf_hs[udc_num_configuration - 1];
    } else
#endif
    {
        // FS descriptor
        udc_ptr_conf = &udc_config.conf_lsfs[udc_num_configuration - 1];
    }
    // Enable all interfaces of the selected configuration
    for (iface_num = 0; iface_num < udc_ptr_conf->desc->bNumInterfaces; iface_num++) {
        if (!udc_iface_enable(iface_num, 0)) {
            return false;
        }
    }
    return true;
}