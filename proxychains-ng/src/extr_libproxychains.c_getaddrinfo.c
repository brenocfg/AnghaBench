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
struct addrinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT () ; 
 int /*<<< orphan*/  PDEBUG (char*,char const*,char const*) ; 
 int proxy_getaddrinfo (char const*,char const*,struct addrinfo const*,struct addrinfo**) ; 
 scalar_t__ proxychains_resolver ; 
 int true_getaddrinfo (char const*,char const*,struct addrinfo const*,struct addrinfo**) ; 

int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res) {
	INIT();
	PDEBUG("getaddrinfo: %s %s\n", node ? node : "null", service ? service : "null");

	if(proxychains_resolver)
		return proxy_getaddrinfo(node, service, hints, res);
	else
		return true_getaddrinfo(node, service, hints, res);
}