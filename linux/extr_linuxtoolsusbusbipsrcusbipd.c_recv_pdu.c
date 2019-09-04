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
typedef  int uint16_t ;

/* Variables and functions */
#define  OP_REQ_CRYPKEY 131 
#define  OP_REQ_DEVINFO 130 
#define  OP_REQ_DEVLIST 129 
#define  OP_REQ_IMPORT 128 
 int OP_UNSPEC ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int /*<<< orphan*/  driver ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int /*<<< orphan*/  info (char*,int,int) ; 
 int recv_request_devlist (int) ; 
 int recv_request_import (int) ; 
 int usbip_net_recv_op_common (int,int*,int*) ; 
 int usbip_refresh_device_list (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int recv_pdu(int connfd)
{
	uint16_t code = OP_UNSPEC;
	int ret;
	int status;

	ret = usbip_net_recv_op_common(connfd, &code, &status);
	if (ret < 0) {
		dbg("could not receive opcode: %#0x", code);
		return -1;
	}

	ret = usbip_refresh_device_list(driver);
	if (ret < 0) {
		dbg("could not refresh device list: %d", ret);
		return -1;
	}

	info("received request: %#0x(%d)", code, connfd);
	switch (code) {
	case OP_REQ_DEVLIST:
		ret = recv_request_devlist(connfd);
		break;
	case OP_REQ_IMPORT:
		ret = recv_request_import(connfd);
		break;
	case OP_REQ_DEVINFO:
	case OP_REQ_CRYPKEY:
	default:
		err("received an unknown opcode: %#0x", code);
		ret = -1;
	}

	if (ret == 0)
		info("request %#0x(%d): complete", code, connfd);
	else
		info("request %#0x(%d): failed", code, connfd);

	return ret;
}