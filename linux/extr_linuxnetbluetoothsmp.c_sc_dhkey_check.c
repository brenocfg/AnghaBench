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
struct smp_cmd_dhkey_check {int /*<<< orphan*/  e; } ;
struct smp_chan {scalar_t__ method; TYPE_1__* conn; int /*<<< orphan*/  rrnd; int /*<<< orphan*/  prnd; int /*<<< orphan*/  mackey; int /*<<< orphan*/  tfm_cmac; int /*<<< orphan*/ * rr; int /*<<< orphan*/ * prsp; int /*<<< orphan*/ * preq; } ;
struct hci_conn {int /*<<< orphan*/  passkey_notify; scalar_t__ out; int /*<<< orphan*/  resp_addr_type; int /*<<< orphan*/  init_addr_type; int /*<<< orphan*/  resp_addr; int /*<<< orphan*/  init_addr; } ;
typedef  int /*<<< orphan*/  r ;
typedef  int /*<<< orphan*/  check ;
struct TYPE_2__ {struct hci_conn* hcon; } ;

/* Variables and functions */
 scalar_t__ DSP_PASSKEY ; 
 scalar_t__ REQ_OOB ; 
 scalar_t__ REQ_PASSKEY ; 
 int /*<<< orphan*/  SMP_CMD_DHKEY_CHECK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_f6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_send_cmd (TYPE_1__*,int /*<<< orphan*/ ,int,struct smp_cmd_dhkey_check*) ; 

__attribute__((used)) static void sc_dhkey_check(struct smp_chan *smp)
{
	struct hci_conn *hcon = smp->conn->hcon;
	struct smp_cmd_dhkey_check check;
	u8 a[7], b[7], *local_addr, *remote_addr;
	u8 io_cap[3], r[16];

	memcpy(a, &hcon->init_addr, 6);
	memcpy(b, &hcon->resp_addr, 6);
	a[6] = hcon->init_addr_type;
	b[6] = hcon->resp_addr_type;

	if (hcon->out) {
		local_addr = a;
		remote_addr = b;
		memcpy(io_cap, &smp->preq[1], 3);
	} else {
		local_addr = b;
		remote_addr = a;
		memcpy(io_cap, &smp->prsp[1], 3);
	}

	memset(r, 0, sizeof(r));

	if (smp->method == REQ_PASSKEY || smp->method == DSP_PASSKEY)
		put_unaligned_le32(hcon->passkey_notify, r);

	if (smp->method == REQ_OOB)
		memcpy(r, smp->rr, 16);

	smp_f6(smp->tfm_cmac, smp->mackey, smp->prnd, smp->rrnd, r, io_cap,
	       local_addr, remote_addr, check.e);

	smp_send_cmd(smp->conn, SMP_CMD_DHKEY_CHECK, sizeof(check), &check);
}