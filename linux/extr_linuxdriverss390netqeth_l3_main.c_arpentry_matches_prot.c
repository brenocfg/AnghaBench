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
struct qeth_arp_entrytype {scalar_t__ ip; } ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 scalar_t__ QETHARP_IP_ADDR_V4 ; 
 scalar_t__ QETHARP_IP_ADDR_V6 ; 
 scalar_t__ QETH_PROT_IPV4 ; 
 scalar_t__ QETH_PROT_IPV6 ; 

__attribute__((used)) static int arpentry_matches_prot(struct qeth_arp_entrytype *type, __u16 prot)
{
	return (type->ip == QETHARP_IP_ADDR_V4 && prot == QETH_PROT_IPV4) ||
		(type->ip == QETHARP_IP_ADDR_V6 && prot == QETH_PROT_IPV6);
}