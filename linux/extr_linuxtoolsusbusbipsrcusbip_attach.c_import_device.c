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
typedef  int /*<<< orphan*/  uint32_t ;
struct usbip_usb_device {int /*<<< orphan*/  speed; int /*<<< orphan*/  devnum; int /*<<< orphan*/  busnum; } ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int /*<<< orphan*/  err (char*) ; 
 scalar_t__ errno ; 
 int usbip_vhci_attach_device (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_vhci_driver_close () ; 
 int usbip_vhci_driver_open () ; 
 int usbip_vhci_get_free_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int import_device(int sockfd, struct usbip_usb_device *udev)
{
	int rc;
	int port;
	uint32_t speed = udev->speed;

	rc = usbip_vhci_driver_open();
	if (rc < 0) {
		err("open vhci_driver");
		goto err_out;
	}

	do {
		port = usbip_vhci_get_free_port(speed);
		if (port < 0) {
			err("no free port");
			goto err_driver_close;
		}

		dbg("got free port %d", port);

		rc = usbip_vhci_attach_device(port, sockfd, udev->busnum,
					      udev->devnum, udev->speed);
		if (rc < 0 && errno != EBUSY) {
			err("import device");
			goto err_driver_close;
		}
	} while (rc < 0);

	usbip_vhci_driver_close();

	return port;

err_driver_close:
	usbip_vhci_driver_close();
err_out:
	return -1;
}