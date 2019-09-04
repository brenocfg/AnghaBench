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
 scalar_t__ TIPC_GRP_MEMBER_EVT ; 
 scalar_t__ msg_type (struct tipc_msg*) ; 

__attribute__((used)) static inline bool msg_is_grp_evt(struct tipc_msg *m)
{
	return msg_type(m) == TIPC_GRP_MEMBER_EVT;
}