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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int BOOTLOADER_SERIAL_MAX_SIZE ; 
 scalar_t__ USB_DEVICE_SERIAL_NAME ; 
 int USB_DEVICE_SERIAL_NAME_SIZE ; 
 int /*<<< orphan*/  _srom ; 
 int const* bootloader_serial_number ; 
 int usb_device_serial_name_size ; 

__attribute__((used)) static const uint8_t *udc_get_string_serial_name(void) {
#if defined           USB_DEVICE_SERIAL_USE_BOOTLOADER_SERIAL
    uint32_t serial_ptrloc  = (uint32_t)&_srom - 4;
    uint32_t serial_address = *(uint32_t *)serial_ptrloc;  // Address of bootloader's serial number if available

    if (serial_address != 0xFFFFFFFF && serial_address < serial_ptrloc)  // Check for factory programmed serial address
    {
        if ((serial_address & 0xFF) % 4 == 0)  // Check alignment
        {
            uint16_t *serial_use    = (uint16_t *)(serial_address);  // Point to address of string in rom
            uint8_t   serial_length = 0;

            while ((*(serial_use + serial_length) > 32 && *(serial_use + serial_length) < 127) && serial_length < BOOTLOADER_SERIAL_MAX_SIZE) {
                bootloader_serial_number[serial_length] = *(serial_use + serial_length) & 0xFF;
                serial_length++;
            }
            bootloader_serial_number[serial_length] = 0;

            usb_device_serial_name_size = serial_length;

            return bootloader_serial_number;  // Use serial programmed into bootloader rom
        }
    }
#endif

    usb_device_serial_name_size = USB_DEVICE_SERIAL_NAME_SIZE;

#if defined USB_DEVICE_SERIAL_NAME
    return (const uint8_t *)USB_DEVICE_SERIAL_NAME;  // Use serial supplied by keyboard's config.h
#else
    return 0;  // No serial supplied
#endif
}