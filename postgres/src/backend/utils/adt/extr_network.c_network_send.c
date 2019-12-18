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
typedef  int /*<<< orphan*/  inet ;
typedef  int /*<<< orphan*/  bytea ;
typedef  int /*<<< orphan*/  StringInfoData ;

/* Variables and functions */
 scalar_t__ ip_addr (int /*<<< orphan*/ *) ; 
 int ip_addrsize (int /*<<< orphan*/ *) ; 
 char ip_bits (int /*<<< orphan*/ *) ; 
 char ip_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_begintypsend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pq_endtypsend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static bytea *
network_send(inet *addr, bool is_cidr)
{
	StringInfoData buf;
	char	   *addrptr;
	int			nb,
				i;

	pq_begintypsend(&buf);
	pq_sendbyte(&buf, ip_family(addr));
	pq_sendbyte(&buf, ip_bits(addr));
	pq_sendbyte(&buf, is_cidr);
	nb = ip_addrsize(addr);
	if (nb < 0)
		nb = 0;
	pq_sendbyte(&buf, nb);
	addrptr = (char *) ip_addr(addr);
	for (i = 0; i < nb; i++)
		pq_sendbyte(&buf, addrptr[i]);
	return pq_endtypsend(&buf);
}