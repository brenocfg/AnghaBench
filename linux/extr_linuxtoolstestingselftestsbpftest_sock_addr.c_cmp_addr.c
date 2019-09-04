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
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr_in6 {scalar_t__ sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct sockaddr_in {scalar_t__ sin_port; TYPE_1__ sin_addr; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cmp_addr(const struct sockaddr_storage *addr1,
		    const struct sockaddr_storage *addr2, int cmp_port)
{
	const struct sockaddr_in *four1, *four2;
	const struct sockaddr_in6 *six1, *six2;

	if (addr1->ss_family != addr2->ss_family)
		return -1;

	if (addr1->ss_family == AF_INET) {
		four1 = (const struct sockaddr_in *)addr1;
		four2 = (const struct sockaddr_in *)addr2;
		return !((four1->sin_port == four2->sin_port || !cmp_port) &&
			 four1->sin_addr.s_addr == four2->sin_addr.s_addr);
	} else if (addr1->ss_family == AF_INET6) {
		six1 = (const struct sockaddr_in6 *)addr1;
		six2 = (const struct sockaddr_in6 *)addr2;
		return !((six1->sin6_port == six2->sin6_port || !cmp_port) &&
			 !memcmp(&six1->sin6_addr, &six2->sin6_addr,
				 sizeof(struct in6_addr)));
	}

	return -1;
}