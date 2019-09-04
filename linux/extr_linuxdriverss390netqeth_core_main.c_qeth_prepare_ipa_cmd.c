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
struct qeth_cmd_buffer {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  ulp_connection_r; } ;
struct qeth_card {TYPE_1__ token; } ;

/* Variables and functions */
 int /*<<< orphan*/ * IPA_PDU_HEADER ; 
 int IPA_PDU_HEADER_SIZE ; 
 int /*<<< orphan*/  QETH_IPA_CMD_DEST_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_IPA_CMD_PROT_TYPE (int /*<<< orphan*/ ) ; 
 int QETH_MPC_TOKEN_LENGTH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qeth_mpc_select_prot_type (struct qeth_card*) ; 

void qeth_prepare_ipa_cmd(struct qeth_card *card, struct qeth_cmd_buffer *iob)
{
	u8 prot_type = qeth_mpc_select_prot_type(card);

	memcpy(iob->data, IPA_PDU_HEADER, IPA_PDU_HEADER_SIZE);
	memcpy(QETH_IPA_CMD_PROT_TYPE(iob->data), &prot_type, 1);
	memcpy(QETH_IPA_CMD_DEST_ADDR(iob->data),
	       &card->token.ulp_connection_r, QETH_MPC_TOKEN_LENGTH);
}