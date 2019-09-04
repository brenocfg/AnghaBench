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
struct sk_buff {int dummy; } ;
struct ip_vs_proto_data {int /*<<< orphan*/ * timeout_table; } ;
struct ip_vs_conn {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int IP_VS_DIR_OUTPUT ; 
 size_t IP_VS_UDP_S_NORMAL ; 
 int /*<<< orphan*/  ip_vs_control_assure_ct (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
udp_state_transition(struct ip_vs_conn *cp, int direction,
		     const struct sk_buff *skb,
		     struct ip_vs_proto_data *pd)
{
	if (unlikely(!pd)) {
		pr_err("UDP no ns data\n");
		return;
	}

	cp->timeout = pd->timeout_table[IP_VS_UDP_S_NORMAL];
	if (direction == IP_VS_DIR_OUTPUT)
		ip_vs_control_assure_ct(cp);
}