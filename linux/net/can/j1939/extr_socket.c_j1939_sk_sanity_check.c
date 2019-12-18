#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pgn; } ;
struct TYPE_4__ {TYPE_1__ j1939; } ;
struct sockaddr_can {scalar_t__ can_family; TYPE_2__ can_addr; int /*<<< orphan*/  can_ifindex; } ;

/* Variables and functions */
 scalar_t__ AF_CAN ; 
 int EDESTADDRREQ ; 
 int EINVAL ; 
 int ENODEV ; 
 int J1939_MIN_NAMELEN ; 
 int /*<<< orphan*/  j1939_pgn_is_clean_pdu (int /*<<< orphan*/ ) ; 
 scalar_t__ j1939_pgn_is_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int j1939_sk_sanity_check(struct sockaddr_can *addr, int len)
{
	if (!addr)
		return -EDESTADDRREQ;
	if (len < J1939_MIN_NAMELEN)
		return -EINVAL;
	if (addr->can_family != AF_CAN)
		return -EINVAL;
	if (!addr->can_ifindex)
		return -ENODEV;
	if (j1939_pgn_is_valid(addr->can_addr.j1939.pgn) &&
	    !j1939_pgn_is_clean_pdu(addr->can_addr.j1939.pgn))
		return -EINVAL;

	return 0;
}