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
struct op_devlist_request {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  memset (struct op_devlist_request*,int /*<<< orphan*/ ,int) ; 
 int send_reply_devlist (int) ; 
 int usbip_net_recv (int,struct op_devlist_request*,int) ; 

__attribute__((used)) static int recv_request_devlist(int connfd)
{
	struct op_devlist_request req;
	int rc;

	memset(&req, 0, sizeof(req));

	rc = usbip_net_recv(connfd, &req, sizeof(req));
	if (rc < 0) {
		dbg("usbip_net_recv failed: devlist request");
		return -1;
	}

	rc = send_reply_devlist(connfd);
	if (rc < 0) {
		dbg("send_reply_devlist failed");
		return -1;
	}

	return 0;
}