#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct netns_ipvs {struct ip_vs_proto_data** proto_data_table; } ;
struct ip_vs_proto_data {TYPE_1__* pp; struct ip_vs_proto_data* next; } ;
struct TYPE_2__ {unsigned short protocol; } ;

/* Variables and functions */
 unsigned int IP_VS_PROTO_HASH (unsigned short) ; 

struct ip_vs_proto_data *
ip_vs_proto_data_get(struct netns_ipvs *ipvs, unsigned short proto)
{
	struct ip_vs_proto_data *pd;
	unsigned int hash = IP_VS_PROTO_HASH(proto);

	for (pd = ipvs->proto_data_table[hash]; pd; pd = pd->next) {
		if (pd->pp->protocol == proto)
			return pd;
	}

	return NULL;
}