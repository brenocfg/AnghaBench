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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  if_nametoindex (char const*) ; 
 int inet_pton (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,char const*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mk_dst_addr(const char *ip, const char *iface,
		       struct sockaddr_in6 *dst)
{
	memset(dst, 0, sizeof(*dst));

	dst->sin6_family = AF_INET6;
	dst->sin6_port = htons(1025);

	if (inet_pton(AF_INET6, ip, &dst->sin6_addr) != 1) {
		log_err("Invalid IPv6: %s", ip);
		return -1;
	}

	dst->sin6_scope_id = if_nametoindex(iface);
	if (!dst->sin6_scope_id) {
		log_err("Failed to get index of iface: %s", iface);
		return -1;
	}

	return 0;
}