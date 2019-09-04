#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int port; int /*<<< orphan*/  operation; int /*<<< orphan*/  protocol; scalar_t__ is_ipv6; int /*<<< orphan*/ * address; } ;
struct TYPE_4__ {TYPE_1__ inet_network; } ;
struct tomoyo_request_info {TYPE_2__ param; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strlen (char*) ; 
 int tomoyo_audit_net_log (struct tomoyo_request_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tomoyo_print_ipv4 (char*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tomoyo_print_ipv6 (char*,int,struct in6_addr const*,struct in6_addr const*) ; 

__attribute__((used)) static int tomoyo_audit_inet_log(struct tomoyo_request_info *r)
{
	char buf[128];
	int len;
	const __be32 *address = r->param.inet_network.address;

	if (r->param.inet_network.is_ipv6)
		tomoyo_print_ipv6(buf, sizeof(buf), (const struct in6_addr *)
				  address, (const struct in6_addr *) address);
	else
		tomoyo_print_ipv4(buf, sizeof(buf), address, address);
	len = strlen(buf);
	snprintf(buf + len, sizeof(buf) - len, " %u",
		 r->param.inet_network.port);
	return tomoyo_audit_net_log(r, "inet", r->param.inet_network.protocol,
				    r->param.inet_network.operation, buf);
}