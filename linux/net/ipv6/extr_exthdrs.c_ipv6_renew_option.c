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
struct ipv6_opt_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_optlen (struct ipv6_opt_hdr*) ; 
 int /*<<< orphan*/  memcpy (char*,struct ipv6_opt_hdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipv6_renew_option(int renewtype,
			      struct ipv6_opt_hdr **dest,
			      struct ipv6_opt_hdr *old,
			      struct ipv6_opt_hdr *new,
			      int newtype, char **p)
{
	struct ipv6_opt_hdr *src;

	src = (renewtype == newtype ? new : old);
	if (!src)
		return;

	memcpy(*p, src, ipv6_optlen(src));
	*dest = (struct ipv6_opt_hdr *)*p;
	*p += CMSG_ALIGN(ipv6_optlen(*dest));
}