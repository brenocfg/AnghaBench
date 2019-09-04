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
typedef  int /*<<< orphan*/  xfrm_address_t ;
struct sockaddr {int dummy; } ;
struct sadb_address {int dummy; } ;

/* Variables and functions */
 int pfkey_sockaddr_extract (struct sockaddr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int pfkey_sadb_addr2xfrm_addr(const struct sadb_address *addr, xfrm_address_t *xaddr)
{
	return pfkey_sockaddr_extract((struct sockaddr *)(addr + 1),
				      xaddr);
}