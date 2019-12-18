#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  busid; } ;
struct op_import_request {TYPE_1__ udev; int /*<<< orphan*/  busid; } ;
struct op_import_reply {TYPE_1__ udev; int /*<<< orphan*/  busid; } ;
typedef  int /*<<< orphan*/  request ;
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 int /*<<< orphan*/  OP_REP_IMPORT ; 
 int /*<<< orphan*/  OP_REQ_IMPORT ; 
 int /*<<< orphan*/  PACK_OP_IMPORT_REPLY (int /*<<< orphan*/ ,struct op_import_request*) ; 
 int /*<<< orphan*/  PACK_OP_IMPORT_REQUEST (int /*<<< orphan*/ ,struct op_import_request*) ; 
 scalar_t__ SYSFS_BUS_ID_SIZE ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int import_device (int,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct op_import_request*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int usbip_net_recv (int,void*,int) ; 
 int usbip_net_recv_op_common (int,int /*<<< orphan*/ *,int*) ; 
 int usbip_net_send (int,void*,int) ; 
 int usbip_net_send_op_common (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_op_common_status_string (int) ; 

__attribute__((used)) static int query_import_device(int sockfd, char *busid)
{
	int rc;
	struct op_import_request request;
	struct op_import_reply   reply;
	uint16_t code = OP_REP_IMPORT;
	int status;

	memset(&request, 0, sizeof(request));
	memset(&reply, 0, sizeof(reply));

	/* send a request */
	rc = usbip_net_send_op_common(sockfd, OP_REQ_IMPORT, 0);
	if (rc < 0) {
		err("send op_common");
		return -1;
	}

	strncpy(request.busid, busid, SYSFS_BUS_ID_SIZE-1);

	PACK_OP_IMPORT_REQUEST(0, &request);

	rc = usbip_net_send(sockfd, (void *) &request, sizeof(request));
	if (rc < 0) {
		err("send op_import_request");
		return -1;
	}

	/* receive a reply */
	rc = usbip_net_recv_op_common(sockfd, &code, &status);
	if (rc < 0) {
		err("Attach Request for %s failed - %s\n",
		    busid, usbip_op_common_status_string(status));
		return -1;
	}

	rc = usbip_net_recv(sockfd, (void *) &reply, sizeof(reply));
	if (rc < 0) {
		err("recv op_import_reply");
		return -1;
	}

	PACK_OP_IMPORT_REPLY(0, &reply);

	/* check the reply */
	if (strncmp(reply.udev.busid, busid, SYSFS_BUS_ID_SIZE)) {
		err("recv different busid %s", reply.udev.busid);
		return -1;
	}

	/* import a device */
	return import_device(sockfd, &reply.udev);
}