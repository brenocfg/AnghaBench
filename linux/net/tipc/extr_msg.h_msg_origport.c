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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_msg {int dummy; } ;

/* Variables and functions */
 scalar_t__ MSG_FRAGMENTER ; 
 struct tipc_msg* msg_inner_hdr (struct tipc_msg*) ; 
 scalar_t__ msg_user (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_word (struct tipc_msg*,int) ; 

__attribute__((used)) static inline u32 msg_origport(struct tipc_msg *m)
{
	if (msg_user(m) == MSG_FRAGMENTER)
		m = msg_inner_hdr(m);
	return msg_word(m, 4);
}