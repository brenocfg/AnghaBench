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
struct TYPE_2__ {int /*<<< orphan*/  default_erl; } ;
struct iscsi_portal_group {TYPE_1__ tpg_attrib; } ;
struct iscsi_node_attrib {int /*<<< orphan*/  default_erl; int /*<<< orphan*/  random_r2t_offsets; int /*<<< orphan*/  random_datain_seq_offsets; int /*<<< orphan*/  random_datain_pdu_offsets; int /*<<< orphan*/  nopin_response_timeout; int /*<<< orphan*/  nopin_timeout; int /*<<< orphan*/  dataout_timeout_retries; int /*<<< orphan*/  dataout_timeout; } ;
struct iscsi_node_acl {struct iscsi_node_attrib node_attrib; } ;

/* Variables and functions */
 int /*<<< orphan*/  NA_DATAOUT_TIMEOUT ; 
 int /*<<< orphan*/  NA_DATAOUT_TIMEOUT_RETRIES ; 
 int /*<<< orphan*/  NA_NOPIN_RESPONSE_TIMEOUT ; 
 int /*<<< orphan*/  NA_NOPIN_TIMEOUT ; 
 int /*<<< orphan*/  NA_RANDOM_DATAIN_PDU_OFFSETS ; 
 int /*<<< orphan*/  NA_RANDOM_DATAIN_SEQ_OFFSETS ; 
 int /*<<< orphan*/  NA_RANDOM_R2T_OFFSETS ; 

void iscsit_set_default_node_attribues(
	struct iscsi_node_acl *acl,
	struct iscsi_portal_group *tpg)
{
	struct iscsi_node_attrib *a = &acl->node_attrib;

	a->dataout_timeout = NA_DATAOUT_TIMEOUT;
	a->dataout_timeout_retries = NA_DATAOUT_TIMEOUT_RETRIES;
	a->nopin_timeout = NA_NOPIN_TIMEOUT;
	a->nopin_response_timeout = NA_NOPIN_RESPONSE_TIMEOUT;
	a->random_datain_pdu_offsets = NA_RANDOM_DATAIN_PDU_OFFSETS;
	a->random_datain_seq_offsets = NA_RANDOM_DATAIN_SEQ_OFFSETS;
	a->random_r2t_offsets = NA_RANDOM_R2T_OFFSETS;
	a->default_erl = tpg->tpg_attrib.default_erl;
}