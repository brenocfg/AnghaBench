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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  tmp ;
struct sockaddr_in6 {scalar_t__ sin6_scope_id; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_flowinfo; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 size_t scnprintf (char*,size_t,char*,scalar_t__,...) ; 

__attribute__((used)) static size_t af_inet6__scnprintf(struct sockaddr *sa, char *bf, size_t size)
{
	struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
	u32 flowinfo = ntohl(sin6->sin6_flowinfo);
	char tmp[512];
	size_t printed = scnprintf(bf, size, ", port: %d, addr: %s", ntohs(sin6->sin6_port),
				   inet_ntop(sin6->sin6_family, &sin6->sin6_addr, tmp, sizeof(tmp)));
	if (flowinfo != 0)
		printed += scnprintf(bf + printed, size - printed, ", flowinfo: %lu", flowinfo);
	if (sin6->sin6_scope_id != 0)
		printed += scnprintf(bf + printed, size - printed, ", scope_id: %lu", sin6->sin6_scope_id);

	return printed;
}