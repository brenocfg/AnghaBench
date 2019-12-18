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

/* Variables and functions */
 int* ip_addr (int /*<<< orphan*/  const*) ; 
 int ip_bits (int /*<<< orphan*/  const*) ; 
 int ip_maxbits (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
inet_spg_node_number(const inet *val, int commonbits)
{
	int			nodeN = 0;

	if (commonbits < ip_maxbits(val) &&
		ip_addr(val)[commonbits / 8] & (1 << (7 - commonbits % 8)))
		nodeN |= 1;
	if (commonbits < ip_bits(val))
		nodeN |= 2;

	return nodeN;
}