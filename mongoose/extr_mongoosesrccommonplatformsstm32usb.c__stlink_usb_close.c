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
struct stlink_libusb {int /*<<< orphan*/  libusb_ctx; int /*<<< orphan*/ * usb_handle; } ;
struct TYPE_3__ {struct stlink_libusb* backend_data; } ;
typedef  TYPE_1__ stlink_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct stlink_libusb* const) ; 
 int /*<<< orphan*/  libusb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb_exit (int /*<<< orphan*/ ) ; 

void _stlink_usb_close(stlink_t *sl) {
  if (!sl) return;

  struct stlink_libusb *const handle = sl->backend_data;
  // maybe we couldn't even get the usb device?
  if (handle != NULL) {
    if (handle->usb_handle != NULL) {
      libusb_close(handle->usb_handle);
    }

    libusb_exit(handle->libusb_ctx);
    free(handle);
  }
}