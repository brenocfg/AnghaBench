#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  pgn; } ;
struct TYPE_4__ {TYPE_1__ addr; } ;
struct j1939_session {TYPE_2__ skcb; struct j1939_priv* priv; } ;
struct j1939_priv {int dummy; } ;

/* Variables and functions */
 int j1939_xtp_do_tx_ctl (struct j1939_priv*,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline int j1939_tp_tx_ctl(struct j1939_session *session,
				  bool swap_src_dst, const u8 *dat)
{
	struct j1939_priv *priv = session->priv;

	return j1939_xtp_do_tx_ctl(priv, &session->skcb,
				   swap_src_dst,
				   session->skcb.addr.pgn, dat);
}