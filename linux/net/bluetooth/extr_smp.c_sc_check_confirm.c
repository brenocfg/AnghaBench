#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct smp_chan {scalar_t__ method; int /*<<< orphan*/  prnd; struct l2cap_conn* conn; } ;
struct l2cap_conn {TYPE_1__* hcon; } ;
struct TYPE_2__ {scalar_t__ out; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 scalar_t__ DSP_PASSKEY ; 
 scalar_t__ REQ_PASSKEY ; 
 int /*<<< orphan*/  SMP_ALLOW_CMD (struct smp_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_CMD_PAIRING_CONFIRM ; 
 int /*<<< orphan*/  SMP_CMD_PAIRING_RANDOM ; 
 int /*<<< orphan*/  sc_passkey_round (struct smp_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 sc_check_confirm(struct smp_chan *smp)
{
	struct l2cap_conn *conn = smp->conn;

	BT_DBG("");

	if (smp->method == REQ_PASSKEY || smp->method == DSP_PASSKEY)
		return sc_passkey_round(smp, SMP_CMD_PAIRING_CONFIRM);

	if (conn->hcon->out) {
		smp_send_cmd(conn, SMP_CMD_PAIRING_RANDOM, sizeof(smp->prnd),
			     smp->prnd);
		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_RANDOM);
	}

	return 0;
}