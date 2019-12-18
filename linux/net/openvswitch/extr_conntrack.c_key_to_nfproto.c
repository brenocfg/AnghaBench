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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct sw_flow_key {TYPE_1__ eth; } ;

/* Variables and functions */
#define  ETH_P_IP 129 
#define  ETH_P_IPV6 128 
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int /*<<< orphan*/  NFPROTO_IPV6 ; 
 int /*<<< orphan*/  NFPROTO_UNSPEC ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 key_to_nfproto(const struct sw_flow_key *key)
{
	switch (ntohs(key->eth.type)) {
	case ETH_P_IP:
		return NFPROTO_IPV4;
	case ETH_P_IPV6:
		return NFPROTO_IPV6;
	default:
		return NFPROTO_UNSPEC;
	}
}