#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* usbd_device_desc; } ;
typedef  TYPE_1__ usbd_cdc_msc_hid_state_t ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int HIBYTE (int /*<<< orphan*/ ) ; 
 int LOBYTE (int /*<<< orphan*/ ) ; 
 int USBD_IDX_MFC_STR ; 
 int USBD_IDX_PRODUCT_STR ; 
 int USBD_IDX_SERIAL_STR ; 
 int USBD_MAX_NUM_CONFIGURATION ; 
 int USB_DESC_TYPE_DEVICE ; 
 int USB_LEN_DEV_DESC ; 
 int USB_MAX_EP0_SIZE ; 

void USBD_SetVIDPIDRelease(usbd_cdc_msc_hid_state_t *usbd, uint16_t vid, uint16_t pid, uint16_t device_release_num, int cdc_only) {
    uint8_t *dev_desc = &usbd->usbd_device_desc[0];

    dev_desc[0] = USB_LEN_DEV_DESC; // bLength
    dev_desc[1] = USB_DESC_TYPE_DEVICE; // bDescriptorType
    dev_desc[2] = 0x00; // bcdUSB
    dev_desc[3] = 0x02; // bcdUSB
    if (cdc_only) {
        // Make it look like a Communications device if we're only
        // using CDC. Otherwise, windows gets confused when we tell it that
        // its a composite device with only a cdc serial interface.
        dev_desc[4] = 0x02; // bDeviceClass
        dev_desc[5] = 0x00; // bDeviceSubClass
        dev_desc[6] = 0x00; // bDeviceProtocol
    } else {
        // For the other modes, we make this look like a composite device.
        dev_desc[4] = 0xef; // bDeviceClass: Miscellaneous Device Class
        dev_desc[5] = 0x02; // bDeviceSubClass: Common Class
        dev_desc[6] = 0x01; // bDeviceProtocol: Interface Association Descriptor
    }
    dev_desc[7] = USB_MAX_EP0_SIZE; // bMaxPacketSize
    dev_desc[8] = LOBYTE(vid); // idVendor
    dev_desc[9] = HIBYTE(vid); // idVendor
    dev_desc[10] = LOBYTE(pid); // idVendor
    dev_desc[11] = HIBYTE(pid); // idVendor
    dev_desc[12] = LOBYTE(device_release_num); // bcdDevice
    dev_desc[13] = HIBYTE(device_release_num); // bcdDevice
    dev_desc[14] = USBD_IDX_MFC_STR; // Index of manufacturer string
    dev_desc[15] = USBD_IDX_PRODUCT_STR; // Index of product string
    dev_desc[16] = USBD_IDX_SERIAL_STR; // Index of serial number string
    dev_desc[17] = USBD_MAX_NUM_CONFIGURATION; // bNumConfigurations
}