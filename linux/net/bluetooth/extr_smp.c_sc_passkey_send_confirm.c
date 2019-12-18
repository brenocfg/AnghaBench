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
typedef  int u8 ;
struct smp_cmd_pairing_confirm {int /*<<< orphan*/  confirm_val; } ;
struct smp_chan {int passkey_round; int /*<<< orphan*/  prnd; int /*<<< orphan*/  remote_pk; int /*<<< orphan*/  local_pk; int /*<<< orphan*/  tfm_cmac; struct l2cap_conn* conn; } ;
struct l2cap_conn {struct hci_conn* hcon; } ;
struct hci_conn {int passkey_notify; } ;
typedef  int /*<<< orphan*/  cfm ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_CMD_PAIRING_CONFIRM ; 
 int SMP_UNSPECIFIED ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int) ; 
 scalar_t__ smp_f4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int,struct smp_cmd_pairing_confirm*) ; 

__attribute__((used)) static u8 sc_passkey_send_confirm(struct smp_chan *smp)
{
	struct l2cap_conn *conn = smp->conn;
	struct hci_conn *hcon = conn->hcon;
	struct smp_cmd_pairing_confirm cfm;
	u8 r;

	r = ((hcon->passkey_notify >> smp->passkey_round) & 0x01);
	r |= 0x80;

	get_random_bytes(smp->prnd, sizeof(smp->prnd));

	if (smp_f4(smp->tfm_cmac, smp->local_pk, smp->remote_pk, smp->prnd, r,
		   cfm.confirm_val))
		return SMP_UNSPECIFIED;

	smp_send_cmd(conn, SMP_CMD_PAIRING_CONFIRM, sizeof(cfm), &cfm);

	return 0;
}