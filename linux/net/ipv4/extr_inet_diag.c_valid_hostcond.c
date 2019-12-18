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
struct inet_diag_hostcond {int family; int prefix_len; } ;
struct inet_diag_bc_op {int dummy; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNSPEC 128 

__attribute__((used)) static bool valid_hostcond(const struct inet_diag_bc_op *op, int len,
			   int *min_len)
{
	struct inet_diag_hostcond *cond;
	int addr_len;

	/* Check hostcond space. */
	*min_len += sizeof(struct inet_diag_hostcond);
	if (len < *min_len)
		return false;
	cond = (struct inet_diag_hostcond *)(op + 1);

	/* Check address family and address length. */
	switch (cond->family) {
	case AF_UNSPEC:
		addr_len = 0;
		break;
	case AF_INET:
		addr_len = sizeof(struct in_addr);
		break;
	case AF_INET6:
		addr_len = sizeof(struct in6_addr);
		break;
	default:
		return false;
	}
	*min_len += addr_len;
	if (len < *min_len)
		return false;

	/* Check prefix length (in bits) vs address length (in bytes). */
	if (cond->prefix_len > 8 * addr_len)
		return false;

	return true;
}