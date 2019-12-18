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
struct sk_buff {int dummy; } ;
struct j1939_session {int /*<<< orphan*/  priv; int /*<<< orphan*/  transmission; } ;

/* Variables and functions */
 int /*<<< orphan*/  j1939_session_deactivate_activate_next (struct j1939_session*) ; 
 struct sk_buff* j1939_session_skb_find (struct j1939_session*) ; 
 int /*<<< orphan*/  j1939_sk_recv (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static void j1939_session_completed(struct j1939_session *session)
{
	struct sk_buff *skb;

	if (!session->transmission) {
		skb = j1939_session_skb_find(session);
		/* distribute among j1939 receivers */
		j1939_sk_recv(session->priv, skb);
	}

	j1939_session_deactivate_activate_next(session);
}