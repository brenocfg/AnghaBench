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
struct pppol2tp_ioc_stats {int /*<<< orphan*/  session_id; } ;
struct l2tp_tunnel {int /*<<< orphan*/  stats; } ;
struct l2tp_session {scalar_t__ pwtype; int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int EBADR ; 
 scalar_t__ L2TP_PWTYPE_PPP ; 
 int /*<<< orphan*/  l2tp_session_dec_refcount (struct l2tp_session*) ; 
 struct l2tp_session* l2tp_tunnel_get_session (struct l2tp_tunnel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pppol2tp_copy_stats (struct pppol2tp_ioc_stats*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pppol2tp_tunnel_copy_stats(struct pppol2tp_ioc_stats *stats,
				      struct l2tp_tunnel *tunnel)
{
	struct l2tp_session *session;

	if (!stats->session_id) {
		pppol2tp_copy_stats(stats, &tunnel->stats);
		return 0;
	}

	/* If session_id is set, search the corresponding session in the
	 * context of this tunnel and record the session's statistics.
	 */
	session = l2tp_tunnel_get_session(tunnel, stats->session_id);
	if (!session)
		return -EBADR;

	if (session->pwtype != L2TP_PWTYPE_PPP) {
		l2tp_session_dec_refcount(session);
		return -EBADR;
	}

	pppol2tp_copy_stats(stats, &session->stats);
	l2tp_session_dec_refcount(session);

	return 0;
}