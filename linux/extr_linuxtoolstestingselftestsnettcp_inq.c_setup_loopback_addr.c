#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in6 {void* sin6_port; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; void* sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr_in {void* sin6_port; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; void* sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
#define  PF_INET 129 
#define  PF_INET6 128 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6addr_loopback ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  port ; 

__attribute__((used)) static void setup_loopback_addr(int family, struct sockaddr_storage *sockaddr)
{
	struct sockaddr_in6 *addr6 = (void *) sockaddr;
	struct sockaddr_in *addr4 = (void *) sockaddr;

	switch (family) {
	case PF_INET:
		memset(addr4, 0, sizeof(*addr4));
		addr4->sin_family = AF_INET;
		addr4->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		addr4->sin_port = htons(port);
		break;
	case PF_INET6:
		memset(addr6, 0, sizeof(*addr6));
		addr6->sin6_family = AF_INET6;
		addr6->sin6_addr = in6addr_loopback;
		addr6->sin6_port = htons(port);
		break;
	default:
		error(1, 0, "illegal family");
	}
}