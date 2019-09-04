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
struct l2tp_tunnel {scalar_t__ magic; } ;
struct l2tp_session {int /*<<< orphan*/  ref_count; struct l2tp_tunnel* tunnel; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ L2TP_TUNNEL_MAGIC ; 
 int /*<<< orphan*/  kfree (struct l2tp_session*) ; 
 int /*<<< orphan*/  l2tp_tunnel_dec_refcount (struct l2tp_tunnel*) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 

void l2tp_session_free(struct l2tp_session *session)
{
	struct l2tp_tunnel *tunnel = session->tunnel;

	BUG_ON(refcount_read(&session->ref_count) != 0);

	if (tunnel) {
		BUG_ON(tunnel->magic != L2TP_TUNNEL_MAGIC);
		l2tp_tunnel_dec_refcount(tunnel);
	}

	kfree(session);
}