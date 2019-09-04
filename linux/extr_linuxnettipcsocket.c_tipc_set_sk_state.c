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
struct sock {int sk_state; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TIPC_CONNECTING 132 
#define  TIPC_DISCONNECTING 131 
#define  TIPC_ESTABLISHED 130 
#define  TIPC_LISTEN 129 
#define  TIPC_OPEN 128 

__attribute__((used)) static int tipc_set_sk_state(struct sock *sk, int state)
{
	int oldsk_state = sk->sk_state;
	int res = -EINVAL;

	switch (state) {
	case TIPC_OPEN:
		res = 0;
		break;
	case TIPC_LISTEN:
	case TIPC_CONNECTING:
		if (oldsk_state == TIPC_OPEN)
			res = 0;
		break;
	case TIPC_ESTABLISHED:
		if (oldsk_state == TIPC_CONNECTING ||
		    oldsk_state == TIPC_OPEN)
			res = 0;
		break;
	case TIPC_DISCONNECTING:
		if (oldsk_state == TIPC_CONNECTING ||
		    oldsk_state == TIPC_ESTABLISHED)
			res = 0;
		break;
	}

	if (!res)
		sk->sk_state = state;

	return res;
}