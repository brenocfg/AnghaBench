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
struct rfcomm_session {scalar_t__ cfc; scalar_t__ mtu; } ;
struct rfcomm_pn {int flow_ctrl; int /*<<< orphan*/  mtu; int /*<<< orphan*/  priority; int /*<<< orphan*/  credits; } ;
struct rfcomm_dlc {scalar_t__ cfc; scalar_t__ mtu; int /*<<< orphan*/  priority; int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_credits; int /*<<< orphan*/  dlci; int /*<<< orphan*/  state; struct rfcomm_session* session; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ RFCOMM_CFC_DISABLED ; 
 scalar_t__ RFCOMM_CFC_ENABLED ; 
 scalar_t__ RFCOMM_CFC_UNKNOWN ; 
 int /*<<< orphan*/  RFCOMM_TX_THROTTLED ; 
 scalar_t__ __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rfcomm_apply_pn(struct rfcomm_dlc *d, int cr, struct rfcomm_pn *pn)
{
	struct rfcomm_session *s = d->session;

	BT_DBG("dlc %p state %ld dlci %d mtu %d fc 0x%x credits %d",
			d, d->state, d->dlci, pn->mtu, pn->flow_ctrl, pn->credits);

	if ((pn->flow_ctrl == 0xf0 && s->cfc != RFCOMM_CFC_DISABLED) ||
						pn->flow_ctrl == 0xe0) {
		d->cfc = RFCOMM_CFC_ENABLED;
		d->tx_credits = pn->credits;
	} else {
		d->cfc = RFCOMM_CFC_DISABLED;
		set_bit(RFCOMM_TX_THROTTLED, &d->flags);
	}

	if (s->cfc == RFCOMM_CFC_UNKNOWN)
		s->cfc = d->cfc;

	d->priority = pn->priority;

	d->mtu = __le16_to_cpu(pn->mtu);

	if (cr && d->mtu > s->mtu)
		d->mtu = s->mtu;

	return 0;
}