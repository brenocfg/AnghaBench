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
typedef  int /*<<< orphan*/  u16 ;
struct tipc_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msg_bits (struct tipc_msg*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u16 msg_grp_bc_ack_req(struct tipc_msg *m)
{
	return msg_bits(m, 10, 0, 0x1);
}