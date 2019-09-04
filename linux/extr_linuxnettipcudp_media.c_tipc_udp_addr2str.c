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
struct udp_media_addr {int /*<<< orphan*/  port; int /*<<< orphan*/  ipv6; int /*<<< orphan*/  proto; int /*<<< orphan*/  ipv4; } ;
struct tipc_media_addr {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tipc_udp_addr2str(struct tipc_media_addr *a, char *buf, int size)
{
	struct udp_media_addr *ua = (struct udp_media_addr *)&a->value;

	if (ntohs(ua->proto) == ETH_P_IP)
		snprintf(buf, size, "%pI4:%u", &ua->ipv4, ntohs(ua->port));
	else if (ntohs(ua->proto) == ETH_P_IPV6)
		snprintf(buf, size, "%pI6:%u", &ua->ipv6, ntohs(ua->port));
	else
		pr_err("Invalid UDP media address\n");
	return 0;
}