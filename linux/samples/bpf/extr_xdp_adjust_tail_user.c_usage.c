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
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void usage(const char *cmd)
{
	printf("Start a XDP prog which send ICMP \"packet too big\" \n"
		"messages if ingress packet is bigger then MAX_SIZE bytes\n");
	printf("Usage: %s [...]\n", cmd);
	printf("    -i <ifname|ifindex> Interface\n");
	printf("    -T <stop-after-X-seconds> Default: 0 (forever)\n");
	printf("    -S use skb-mode\n");
	printf("    -N enforce native mode\n");
	printf("    -F force loading prog\n");
	printf("    -h Display this help\n");
}