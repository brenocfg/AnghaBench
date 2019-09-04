#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_11__ {size_t type; int /*<<< orphan*/  mode; int /*<<< orphan*/  numfrm; int /*<<< orphan*/  nwwn; int /*<<< orphan*/  pwwn; } ;
struct TYPE_10__ {size_t status; size_t speed; size_t* subtest_status; int /*<<< orphan*/  frm_sz; int /*<<< orphan*/  numbuffer; int /*<<< orphan*/  distance; int /*<<< orphan*/  latency; } ;
struct TYPE_12__ {TYPE_4__ teststart; TYPE_3__ testcomp; } ;
struct bfi_diag_dport_scn_s {size_t state; TYPE_5__ info; } ;
struct TYPE_14__ {size_t end_time; size_t status; size_t roundtrip_latency; size_t est_cable_distance; size_t buffer_required; size_t frmsz; size_t speed; TYPE_6__* subtest; } ;
struct TYPE_8__ {size_t state; } ;
struct TYPE_9__ {TYPE_1__ scn; } ;
struct bfa_dport_s {int /*<<< orphan*/  bfa; TYPE_7__ result; void* lpcnt; int /*<<< orphan*/  rp_nwwn; int /*<<< orphan*/  rp_pwwn; TYPE_2__ i2hmsg; } ;
struct bfa_diag_dport_result_s {int dummy; } ;
struct TYPE_13__ {size_t status; size_t start_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_DPORT_SM_SCN ; 
#define  BFI_DPORT_SCN_DDPORT_DISABLE 136 
#define  BFI_DPORT_SCN_DDPORT_DISABLED 135 
#define  BFI_DPORT_SCN_DDPORT_ENABLE 134 
#define  BFI_DPORT_SCN_FCPORT_DISABLE 133 
#define  BFI_DPORT_SCN_SFP_REMOVED 132 
#define  BFI_DPORT_SCN_SUBTESTSTART 131 
#define  BFI_DPORT_SCN_TESTCOMP 130 
#define  BFI_DPORT_SCN_TESTSKIP 129 
#define  BFI_DPORT_SCN_TESTSTART 128 
 int DPORT_TEST_ELOOP ; 
 int DPORT_TEST_MAX ; 
 size_t DPORT_TEST_ST_IDLE ; 
 size_t DPORT_TEST_ST_INPRG ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_dport_result_start (struct bfa_dport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_dport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,size_t) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* ktime_get_real_seconds () ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_dport_scn(struct bfa_dport_s *dport, struct bfi_diag_dport_scn_s *msg)
{
	int i;
	uint8_t subtesttype;

	bfa_trc(dport->bfa, msg->state);
	dport->i2hmsg.scn.state = msg->state;

	switch (dport->i2hmsg.scn.state) {
	case BFI_DPORT_SCN_TESTCOMP:
		dport->result.end_time = ktime_get_real_seconds();
		bfa_trc(dport->bfa, dport->result.end_time);

		dport->result.status = msg->info.testcomp.status;
		bfa_trc(dport->bfa, dport->result.status);

		dport->result.roundtrip_latency =
			cpu_to_be32(msg->info.testcomp.latency);
		dport->result.est_cable_distance =
			cpu_to_be32(msg->info.testcomp.distance);
		dport->result.buffer_required =
			be16_to_cpu(msg->info.testcomp.numbuffer);

		dport->result.frmsz = be16_to_cpu(msg->info.testcomp.frm_sz);
		dport->result.speed = msg->info.testcomp.speed;

		bfa_trc(dport->bfa, dport->result.roundtrip_latency);
		bfa_trc(dport->bfa, dport->result.est_cable_distance);
		bfa_trc(dport->bfa, dport->result.buffer_required);
		bfa_trc(dport->bfa, dport->result.frmsz);
		bfa_trc(dport->bfa, dport->result.speed);

		for (i = DPORT_TEST_ELOOP; i < DPORT_TEST_MAX; i++) {
			dport->result.subtest[i].status =
				msg->info.testcomp.subtest_status[i];
			bfa_trc(dport->bfa, dport->result.subtest[i].status);
		}
		break;

	case BFI_DPORT_SCN_TESTSKIP:
	case BFI_DPORT_SCN_DDPORT_ENABLE:
		memset(&dport->result, 0,
				sizeof(struct bfa_diag_dport_result_s));
		break;

	case BFI_DPORT_SCN_TESTSTART:
		memset(&dport->result, 0,
				sizeof(struct bfa_diag_dport_result_s));
		dport->rp_pwwn = msg->info.teststart.pwwn;
		dport->rp_nwwn = msg->info.teststart.nwwn;
		dport->lpcnt = cpu_to_be32(msg->info.teststart.numfrm);
		bfa_dport_result_start(dport, msg->info.teststart.mode);
		break;

	case BFI_DPORT_SCN_SUBTESTSTART:
		subtesttype = msg->info.teststart.type;
		dport->result.subtest[subtesttype].start_time =
			ktime_get_real_seconds();
		dport->result.subtest[subtesttype].status =
			DPORT_TEST_ST_INPRG;

		bfa_trc(dport->bfa, subtesttype);
		bfa_trc(dport->bfa,
			dport->result.subtest[subtesttype].start_time);
		break;

	case BFI_DPORT_SCN_SFP_REMOVED:
	case BFI_DPORT_SCN_DDPORT_DISABLED:
	case BFI_DPORT_SCN_DDPORT_DISABLE:
	case BFI_DPORT_SCN_FCPORT_DISABLE:
		dport->result.status = DPORT_TEST_ST_IDLE;
		break;

	default:
		bfa_sm_fault(dport->bfa, msg->state);
	}

	bfa_sm_send_event(dport, BFA_DPORT_SM_SCN);
}