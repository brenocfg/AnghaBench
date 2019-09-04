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
struct ip_vs_proto_data {int /*<<< orphan*/ * timeout_table; } ;
struct ip_vs_conn {size_t state; int /*<<< orphan*/  lock; int /*<<< orphan*/  timeout; int /*<<< orphan*/  ipvs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 size_t IP_VS_TCP_S_LISTEN ; 
 struct ip_vs_proto_data* ip_vs_proto_data_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tcp_timeouts ; 

void ip_vs_tcp_conn_listen(struct ip_vs_conn *cp)
{
	struct ip_vs_proto_data *pd = ip_vs_proto_data_get(cp->ipvs, IPPROTO_TCP);

	spin_lock_bh(&cp->lock);
	cp->state = IP_VS_TCP_S_LISTEN;
	cp->timeout = (pd ? pd->timeout_table[IP_VS_TCP_S_LISTEN]
			   : tcp_timeouts[IP_VS_TCP_S_LISTEN]);
	spin_unlock_bh(&cp->lock);
}