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
typedef  int u32 ;
struct tipc_msg {int dummy; } ;

/* Variables and functions */
 int MSG_BUNDLER ; 
 int MSG_FRAGMENTER ; 
 int TIPC_CRITICAL_IMPORTANCE ; 
 int TIPC_SYSTEM_IMPORTANCE ; 
 scalar_t__ likely (int) ; 
 int msg_bits (struct tipc_msg*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_errcode (struct tipc_msg*) ; 
 int msg_user (struct tipc_msg*) ; 

__attribute__((used)) static inline u32 msg_importance(struct tipc_msg *m)
{
	int usr = msg_user(m);

	if (likely((usr <= TIPC_CRITICAL_IMPORTANCE) && !msg_errcode(m)))
		return usr;
	if ((usr == MSG_FRAGMENTER) || (usr == MSG_BUNDLER))
		return msg_bits(m, 9, 0, 0x7);
	return TIPC_SYSTEM_IMPORTANCE;
}