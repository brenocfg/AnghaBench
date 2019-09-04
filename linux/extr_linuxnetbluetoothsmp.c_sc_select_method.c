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
typedef  scalar_t__ u8 ;
struct smp_cmd_pairing {scalar_t__ io_capability; scalar_t__ auth_req; } ;
struct smp_chan {int /*<<< orphan*/  flags; int /*<<< orphan*/ * preq; int /*<<< orphan*/ * prsp; struct l2cap_conn* conn; } ;
struct l2cap_conn {struct hci_conn* hcon; } ;
struct hci_conn {scalar_t__ out; } ;

/* Variables and functions */
 scalar_t__ JUST_CFM ; 
 scalar_t__ JUST_WORKS ; 
 scalar_t__ REQ_OOB ; 
 scalar_t__ SMP_AUTH_MITM ; 
 int /*<<< orphan*/  SMP_FLAG_INITIATOR ; 
 int /*<<< orphan*/  SMP_FLAG_LOCAL_OOB ; 
 int /*<<< orphan*/  SMP_FLAG_REMOTE_OOB ; 
 scalar_t__ get_auth_method (struct smp_chan*,scalar_t__,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 sc_select_method(struct smp_chan *smp)
{
	struct l2cap_conn *conn = smp->conn;
	struct hci_conn *hcon = conn->hcon;
	struct smp_cmd_pairing *local, *remote;
	u8 local_mitm, remote_mitm, local_io, remote_io, method;

	if (test_bit(SMP_FLAG_REMOTE_OOB, &smp->flags) ||
	    test_bit(SMP_FLAG_LOCAL_OOB, &smp->flags))
		return REQ_OOB;

	/* The preq/prsp contain the raw Pairing Request/Response PDUs
	 * which are needed as inputs to some crypto functions. To get
	 * the "struct smp_cmd_pairing" from them we need to skip the
	 * first byte which contains the opcode.
	 */
	if (hcon->out) {
		local = (void *) &smp->preq[1];
		remote = (void *) &smp->prsp[1];
	} else {
		local = (void *) &smp->prsp[1];
		remote = (void *) &smp->preq[1];
	}

	local_io = local->io_capability;
	remote_io = remote->io_capability;

	local_mitm = (local->auth_req & SMP_AUTH_MITM);
	remote_mitm = (remote->auth_req & SMP_AUTH_MITM);

	/* If either side wants MITM, look up the method from the table,
	 * otherwise use JUST WORKS.
	 */
	if (local_mitm || remote_mitm)
		method = get_auth_method(smp, local_io, remote_io);
	else
		method = JUST_WORKS;

	/* Don't confirm locally initiated pairing attempts */
	if (method == JUST_CFM && test_bit(SMP_FLAG_INITIATOR, &smp->flags))
		method = JUST_WORKS;

	return method;
}