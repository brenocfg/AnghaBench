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
struct atm_mpoa_qos {scalar_t__ ipaddr; struct atm_mpoa_qos* next; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 struct atm_mpoa_qos* qos_head ; 

struct atm_mpoa_qos *atm_mpoa_search_qos(__be32 dst_ip)
{
	struct atm_mpoa_qos *qos;

	qos = qos_head;
	while (qos) {
		if (qos->ipaddr == dst_ip)
			break;
		qos = qos->next;
	}

	return qos;
}