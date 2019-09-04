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
typedef  int /*<<< orphan*/  uintf ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  udev ;
struct usbip_usb_interface {unsigned int ndev; char* busid; char* path; int bNumInterfaces; int /*<<< orphan*/  bInterfaceProtocol; int /*<<< orphan*/  bInterfaceSubClass; int /*<<< orphan*/  bInterfaceClass; int /*<<< orphan*/  bDeviceProtocol; int /*<<< orphan*/  bDeviceSubClass; int /*<<< orphan*/  bDeviceClass; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usbip_usb_device {unsigned int ndev; char* busid; char* path; int bNumInterfaces; int /*<<< orphan*/  bInterfaceProtocol; int /*<<< orphan*/  bInterfaceSubClass; int /*<<< orphan*/  bInterfaceClass; int /*<<< orphan*/  bDeviceProtocol; int /*<<< orphan*/  bDeviceSubClass; int /*<<< orphan*/  bDeviceClass; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct op_devlist_reply {unsigned int ndev; char* busid; char* path; int bNumInterfaces; int /*<<< orphan*/  bInterfaceProtocol; int /*<<< orphan*/  bInterfaceSubClass; int /*<<< orphan*/  bInterfaceClass; int /*<<< orphan*/  bDeviceProtocol; int /*<<< orphan*/  bDeviceSubClass; int /*<<< orphan*/  bDeviceClass; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  product_name ;
typedef  int /*<<< orphan*/  class_name ;

/* Variables and functions */
 int /*<<< orphan*/  OP_REP_DEVLIST ; 
 int /*<<< orphan*/  OP_REQ_DEVLIST ; 
 int /*<<< orphan*/  PACK_OP_DEVLIST_REPLY (int /*<<< orphan*/ ,struct usbip_usb_interface*) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 int /*<<< orphan*/  memset (struct usbip_usb_interface*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  usbip_names_get_class (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_names_get_product (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_net_pack_usb_device (int /*<<< orphan*/ ,struct usbip_usb_interface*) ; 
 int /*<<< orphan*/  usbip_net_pack_usb_interface (int /*<<< orphan*/ ,struct usbip_usb_interface*) ; 
 int usbip_net_recv (int,struct usbip_usb_interface*,int) ; 
 int usbip_net_recv_op_common (int,int /*<<< orphan*/ *,int*) ; 
 int usbip_net_send_op_common (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usbip_op_common_status_string (int) ; 

__attribute__((used)) static int get_exported_devices(char *host, int sockfd)
{
	char product_name[100];
	char class_name[100];
	struct op_devlist_reply reply;
	uint16_t code = OP_REP_DEVLIST;
	struct usbip_usb_device udev;
	struct usbip_usb_interface uintf;
	unsigned int i;
	int rc, j;
	int status;

	rc = usbip_net_send_op_common(sockfd, OP_REQ_DEVLIST, 0);
	if (rc < 0) {
		dbg("usbip_net_send_op_common failed");
		return -1;
	}

	rc = usbip_net_recv_op_common(sockfd, &code, &status);
	if (rc < 0) {
		err("Exported Device List Request failed - %s\n",
		    usbip_op_common_status_string(status));
		return -1;
	}

	memset(&reply, 0, sizeof(reply));
	rc = usbip_net_recv(sockfd, &reply, sizeof(reply));
	if (rc < 0) {
		dbg("usbip_net_recv_op_devlist failed");
		return -1;
	}
	PACK_OP_DEVLIST_REPLY(0, &reply);
	dbg("exportable devices: %d\n", reply.ndev);

	if (reply.ndev == 0) {
		info("no exportable devices found on %s", host);
		return 0;
	}

	printf("Exportable USB devices\n");
	printf("======================\n");
	printf(" - %s\n", host);

	for (i = 0; i < reply.ndev; i++) {
		memset(&udev, 0, sizeof(udev));
		rc = usbip_net_recv(sockfd, &udev, sizeof(udev));
		if (rc < 0) {
			dbg("usbip_net_recv failed: usbip_usb_device[%d]", i);
			return -1;
		}
		usbip_net_pack_usb_device(0, &udev);

		usbip_names_get_product(product_name, sizeof(product_name),
					udev.idVendor, udev.idProduct);
		usbip_names_get_class(class_name, sizeof(class_name),
				      udev.bDeviceClass, udev.bDeviceSubClass,
				      udev.bDeviceProtocol);
		printf("%11s: %s\n", udev.busid, product_name);
		printf("%11s: %s\n", "", udev.path);
		printf("%11s: %s\n", "", class_name);

		for (j = 0; j < udev.bNumInterfaces; j++) {
			rc = usbip_net_recv(sockfd, &uintf, sizeof(uintf));
			if (rc < 0) {
				err("usbip_net_recv failed: usbip_usb_intf[%d]",
						j);

				return -1;
			}
			usbip_net_pack_usb_interface(0, &uintf);

			usbip_names_get_class(class_name, sizeof(class_name),
					uintf.bInterfaceClass,
					uintf.bInterfaceSubClass,
					uintf.bInterfaceProtocol);
			printf("%11s: %2d - %s\n", "", j, class_name);
		}

		printf("\n");
	}

	return 0;
}