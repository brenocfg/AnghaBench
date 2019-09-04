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
struct tomoyo_unix_addr_info {unsigned int addr_len; int /*<<< orphan*/  addr; } ;
struct tomoyo_addr_info {struct tomoyo_unix_addr_info unix0; } ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; } ;
struct sockaddr {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 int tomoyo_unix_entry (struct tomoyo_addr_info*) ; 

__attribute__((used)) static int tomoyo_check_unix_address(struct sockaddr *addr,
				     const unsigned int addr_len,
				     struct tomoyo_addr_info *address)
{
	struct tomoyo_unix_addr_info *u = &address->unix0;

	if (addr->sa_family != AF_UNIX)
		return 0;
	u->addr = ((struct sockaddr_un *) addr)->sun_path;
	u->addr_len = addr_len;
	return tomoyo_unix_entry(address);
}