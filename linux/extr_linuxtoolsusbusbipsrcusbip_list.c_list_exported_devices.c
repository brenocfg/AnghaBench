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
 int /*<<< orphan*/  dbg (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*,char*,...) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int get_exported_devices (char*,int) ; 
 int usbip_net_tcp_connect (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_port_string ; 

__attribute__((used)) static int list_exported_devices(char *host)
{
	int rc;
	int sockfd;

	sockfd = usbip_net_tcp_connect(host, usbip_port_string);
	if (sockfd < 0) {
		err("could not connect to %s:%s: %s", host,
		    usbip_port_string, gai_strerror(sockfd));
		return -1;
	}
	dbg("connected to %s:%s", host, usbip_port_string);

	rc = get_exported_devices(host, sockfd);
	if (rc < 0) {
		err("failed to get device list from %s", host);
		return -1;
	}

	close(sockfd);

	return 0;
}