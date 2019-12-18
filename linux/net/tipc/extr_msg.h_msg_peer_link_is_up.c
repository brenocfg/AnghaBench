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
 scalar_t__ LINK_PROTOCOL ; 
 scalar_t__ STATE_MSG ; 
 scalar_t__ likely (int) ; 
 scalar_t__ msg_type (struct tipc_msg*) ; 
 scalar_t__ msg_user (struct tipc_msg*) ; 

__attribute__((used)) static inline bool msg_peer_link_is_up(struct tipc_msg *m)
{
	if (likely(msg_user(m) != LINK_PROTOCOL))
		return true;
	if (msg_type(m) == STATE_MSG)
		return true;
	return false;
}