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
 int TIPC_GRP_MEMBER_EVT ; 
 int TIPC_GRP_UCAST_MSG ; 
 int msg_type (struct tipc_msg*) ; 

__attribute__((used)) static inline int msg_in_group(struct tipc_msg *m)
{
	int mtyp = msg_type(m);

	return mtyp >= TIPC_GRP_MEMBER_EVT && mtyp <= TIPC_GRP_UCAST_MSG;
}