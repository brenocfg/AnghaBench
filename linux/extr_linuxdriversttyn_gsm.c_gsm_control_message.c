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
typedef  unsigned int u8 ;
struct gsm_mux {int dead; int constipated; int /*<<< orphan*/  tx_lock; struct gsm_dlci** dlci; } ;
struct gsm_dlci {int dead; } ;

/* Variables and functions */
#define  CMD_CLD 137 
#define  CMD_FCOFF 136 
#define  CMD_FCON 135 
#define  CMD_MSC 134 
 int const CMD_NSC ; 
#define  CMD_PN 133 
#define  CMD_PSC 132 
#define  CMD_RLS 131 
#define  CMD_RPN 130 
#define  CMD_SNC 129 
#define  CMD_TEST 128 
 int /*<<< orphan*/  gsm_control_modem (struct gsm_mux*,unsigned int*,int) ; 
 int /*<<< orphan*/  gsm_control_reply (struct gsm_mux*,int const,unsigned int*,int) ; 
 int /*<<< orphan*/  gsm_control_rls (struct gsm_mux*,unsigned int*,int) ; 
 int /*<<< orphan*/  gsm_data_kick (struct gsm_mux*) ; 
 int /*<<< orphan*/  gsm_dlci_begin_close (struct gsm_dlci*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gsm_control_message(struct gsm_mux *gsm, unsigned int command,
							u8 *data, int clen)
{
	u8 buf[1];
	unsigned long flags;

	switch (command) {
	case CMD_CLD: {
		struct gsm_dlci *dlci = gsm->dlci[0];
		/* Modem wishes to close down */
		if (dlci) {
			dlci->dead = 1;
			gsm->dead = 1;
			gsm_dlci_begin_close(dlci);
		}
		}
		break;
	case CMD_TEST:
		/* Modem wishes to test, reply with the data */
		gsm_control_reply(gsm, CMD_TEST, data, clen);
		break;
	case CMD_FCON:
		/* Modem can accept data again */
		gsm->constipated = 0;
		gsm_control_reply(gsm, CMD_FCON, NULL, 0);
		/* Kick the link in case it is idling */
		spin_lock_irqsave(&gsm->tx_lock, flags);
		gsm_data_kick(gsm);
		spin_unlock_irqrestore(&gsm->tx_lock, flags);
		break;
	case CMD_FCOFF:
		/* Modem wants us to STFU */
		gsm->constipated = 1;
		gsm_control_reply(gsm, CMD_FCOFF, NULL, 0);
		break;
	case CMD_MSC:
		/* Out of band modem line change indicator for a DLCI */
		gsm_control_modem(gsm, data, clen);
		break;
	case CMD_RLS:
		/* Out of band error reception for a DLCI */
		gsm_control_rls(gsm, data, clen);
		break;
	case CMD_PSC:
		/* Modem wishes to enter power saving state */
		gsm_control_reply(gsm, CMD_PSC, NULL, 0);
		break;
		/* Optional unsupported commands */
	case CMD_PN:	/* Parameter negotiation */
	case CMD_RPN:	/* Remote port negotiation */
	case CMD_SNC:	/* Service negotiation command */
	default:
		/* Reply to bad commands with an NSC */
		buf[0] = command;
		gsm_control_reply(gsm, CMD_NSC, buf, 1);
		break;
	}
}