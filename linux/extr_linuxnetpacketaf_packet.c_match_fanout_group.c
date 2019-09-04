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
struct sock {scalar_t__ sk_family; } ;
struct packet_type {scalar_t__ af_packet_priv; } ;
struct TYPE_2__ {scalar_t__ fanout; } ;

/* Variables and functions */
 scalar_t__ PF_PACKET ; 
 TYPE_1__* pkt_sk (struct sock*) ; 

__attribute__((used)) static bool match_fanout_group(struct packet_type *ptype, struct sock *sk)
{
	if (sk->sk_family != PF_PACKET)
		return false;

	return ptype->af_packet_priv == pkt_sk(sk)->fanout;
}