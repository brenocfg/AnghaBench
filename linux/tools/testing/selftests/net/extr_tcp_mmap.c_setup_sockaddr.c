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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; void* sin6_port; void* sin6_family; int /*<<< orphan*/  sin_addr; void* sin_port; void* sin_family; } ;
struct sockaddr_in {int /*<<< orphan*/  sin6_addr; void* sin6_port; void* sin6_family; int /*<<< orphan*/  sin_addr; void* sin_port; void* sin_family; } ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_INET6 ; 
#define  PF_INET 129 
#define  PF_INET6 128 
 int /*<<< orphan*/  cfg_port ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int inet_pton (void*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setup_sockaddr(int domain, const char *str_addr,
			   struct sockaddr_storage *sockaddr)
{
	struct sockaddr_in6 *addr6 = (void *) sockaddr;
	struct sockaddr_in *addr4 = (void *) sockaddr;

	switch (domain) {
	case PF_INET:
		memset(addr4, 0, sizeof(*addr4));
		addr4->sin_family = AF_INET;
		addr4->sin_port = htons(cfg_port);
		if (str_addr &&
		    inet_pton(AF_INET, str_addr, &(addr4->sin_addr)) != 1)
			error(1, 0, "ipv4 parse error: %s", str_addr);
		break;
	case PF_INET6:
		memset(addr6, 0, sizeof(*addr6));
		addr6->sin6_family = AF_INET6;
		addr6->sin6_port = htons(cfg_port);
		if (str_addr &&
		    inet_pton(AF_INET6, str_addr, &(addr6->sin6_addr)) != 1)
			error(1, 0, "ipv6 parse error: %s", str_addr);
		break;
	default:
		error(1, 0, "illegal domain");
	}
}