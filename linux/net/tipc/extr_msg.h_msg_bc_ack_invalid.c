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
struct tipc_msg {int dummy; } ;

/* Variables and functions */
#define  BCAST_PROTOCOL 130 
#define  LINK_PROTOCOL 129 
#define  NAME_DISTRIBUTOR 128 
 int msg_bits (struct tipc_msg*,int,int,int) ; 
 int msg_user (struct tipc_msg*) ; 

__attribute__((used)) static inline bool msg_bc_ack_invalid(struct tipc_msg *m)
{
	switch (msg_user(m)) {
	case BCAST_PROTOCOL:
	case NAME_DISTRIBUTOR:
	case LINK_PROTOCOL:
		return msg_bits(m, 5, 14, 0x1);
	default:
		return false;
	}
}