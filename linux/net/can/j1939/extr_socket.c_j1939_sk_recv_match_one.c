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
struct j1939_sock {int state; } ;
struct j1939_sk_buff_cb {int dummy; } ;

/* Variables and functions */
 int J1939_SOCK_BOUND ; 
 int /*<<< orphan*/  j1939_sk_match_dst (struct j1939_sock*,struct j1939_sk_buff_cb const*) ; 
 int /*<<< orphan*/  j1939_sk_match_filter (struct j1939_sock*,struct j1939_sk_buff_cb const*) ; 

__attribute__((used)) static bool j1939_sk_recv_match_one(struct j1939_sock *jsk,
				    const struct j1939_sk_buff_cb *skcb)
{
	if (!(jsk->state & J1939_SOCK_BOUND))
		return false;

	if (!j1939_sk_match_dst(jsk, skcb))
		return false;

	if (!j1939_sk_match_filter(jsk, skcb))
		return false;

	return true;
}