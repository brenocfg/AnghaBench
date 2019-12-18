#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pgn; } ;
struct TYPE_5__ {TYPE_1__ addr; } ;
struct j1939_session {int /*<<< orphan*/  err; scalar_t__ sk; TYPE_2__ skcb; int /*<<< orphan*/  transmission; int /*<<< orphan*/  state; struct j1939_priv* priv; } ;
struct j1939_priv {int dummy; } ;
typedef  enum j1939_xtp_abort { ____Placeholder_j1939_xtp_abort } j1939_xtp_abort ;

/* Variables and functions */
 int /*<<< orphan*/  J1939_SESSION_WAITING_ABORT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  j1939_cb_is_broadcast (TYPE_2__*) ; 
 int /*<<< orphan*/  j1939_sk_send_loop_abort (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  j1939_xtp_abort_to_errno (struct j1939_priv*,int) ; 
 int /*<<< orphan*/  j1939_xtp_tx_abort (struct j1939_priv*,TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void j1939_session_cancel(struct j1939_session *session,
				 enum j1939_xtp_abort err)
{
	struct j1939_priv *priv = session->priv;

	WARN_ON_ONCE(!err);

	session->err = j1939_xtp_abort_to_errno(priv, err);
	/* do not send aborts on incoming broadcasts */
	if (!j1939_cb_is_broadcast(&session->skcb)) {
		session->state = J1939_SESSION_WAITING_ABORT;
		j1939_xtp_tx_abort(priv, &session->skcb,
				   !session->transmission,
				   err, session->skcb.addr.pgn);
	}

	if (session->sk)
		j1939_sk_send_loop_abort(session->sk, session->err);
}