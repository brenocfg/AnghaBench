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

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (char*) ; 
 int query_import_device (int,char*) ; 
 int record_connection (char*,int /*<<< orphan*/ ,char*,int) ; 
 int usbip_net_tcp_connect (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_port_string ; 

__attribute__((used)) static int attach_device(char *host, char *busid)
{
	int sockfd;
	int rc;
	int rhport;

	sockfd = usbip_net_tcp_connect(host, usbip_port_string);
	if (sockfd < 0) {
		err("tcp connect");
		return -1;
	}

	rhport = query_import_device(sockfd, busid);
	if (rhport < 0)
		return -1;

	close(sockfd);

	rc = record_connection(host, usbip_port_string, busid, rhport);
	if (rc < 0) {
		err("record connection");
		return -1;
	}

	return 0;
}