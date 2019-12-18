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
struct smp_cmd_pairing_confirm {int /*<<< orphan*/  confirm_val; } ;
struct smp_chan {struct l2cap_conn* conn; int /*<<< orphan*/  flags; int /*<<< orphan*/  prsp; int /*<<< orphan*/  preq; int /*<<< orphan*/  prnd; int /*<<< orphan*/  tk; } ;
struct l2cap_conn {TYPE_1__* hcon; } ;
typedef  int /*<<< orphan*/  cp ;
struct TYPE_2__ {scalar_t__ out; int /*<<< orphan*/  resp_addr; int /*<<< orphan*/  resp_addr_type; int /*<<< orphan*/  init_addr; int /*<<< orphan*/  init_addr_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_conn*) ; 
 int /*<<< orphan*/  SMP_ALLOW_CMD (struct smp_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_CMD_PAIRING_CONFIRM ; 
 int /*<<< orphan*/  SMP_CMD_PAIRING_RANDOM ; 
 int /*<<< orphan*/  SMP_FLAG_CFM_PENDING ; 
 int /*<<< orphan*/  SMP_UNSPECIFIED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int smp_c1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int,struct smp_cmd_pairing_confirm*) ; 

__attribute__((used)) static u8 smp_confirm(struct smp_chan *smp)
{
	struct l2cap_conn *conn = smp->conn;
	struct smp_cmd_pairing_confirm cp;
	int ret;

	BT_DBG("conn %p", conn);

	ret = smp_c1(smp->tk, smp->prnd, smp->preq, smp->prsp,
		     conn->hcon->init_addr_type, &conn->hcon->init_addr,
		     conn->hcon->resp_addr_type, &conn->hcon->resp_addr,
		     cp.confirm_val);
	if (ret)
		return SMP_UNSPECIFIED;

	clear_bit(SMP_FLAG_CFM_PENDING, &smp->flags);

	smp_send_cmd(smp->conn, SMP_CMD_PAIRING_CONFIRM, sizeof(cp), &cp);

	if (conn->hcon->out)
		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_CONFIRM);
	else
		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_RANDOM);

	return 0;
}