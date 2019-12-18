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
struct pktgen_dev {unsigned int nr_labels; int* labels; } ;
typedef  int __be32 ;

/* Variables and functions */
 int MPLS_STACK_BOTTOM ; 

__attribute__((used)) static void mpls_push(__be32 *mpls, struct pktgen_dev *pkt_dev)
{
	unsigned int i;
	for (i = 0; i < pkt_dev->nr_labels; i++)
		*mpls++ = pkt_dev->labels[i] & ~MPLS_STACK_BOTTOM;

	mpls--;
	*mpls |= MPLS_STACK_BOTTOM;
}