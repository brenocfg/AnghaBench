#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ expires; } ;
struct ibmvfc_target {int cancel_key; int /*<<< orphan*/  kref; TYPE_6__ timer; int /*<<< orphan*/  scsi_id; struct ibmvfc_host* vhost; } ;
struct TYPE_12__ {void** payload; } ;
struct TYPE_11__ {void* cancel_key; int /*<<< orphan*/  scsi_id; void* flags; } ;
struct ibmvfc_passthru_mad {TYPE_3__ fc_iu; TYPE_2__ iu; } ;
struct ibmvfc_host {scalar_t__ discovery_threads; TYPE_5__* login_buf; } ;
struct TYPE_10__ {struct ibmvfc_passthru_mad passthru; } ;
struct ibmvfc_event {TYPE_1__ iu; struct ibmvfc_target* tgt; } ;
struct TYPE_13__ {int /*<<< orphan*/  scsi_id; int /*<<< orphan*/  node_name; int /*<<< orphan*/  port_name; } ;
struct TYPE_14__ {TYPE_4__ resp; } ;

/* Variables and functions */
 int HZ ; 
 int IBMVFC_ADISC ; 
 int /*<<< orphan*/  IBMVFC_ADISC_PLUS_CANCEL_TIMEOUT ; 
 int IBMVFC_ADISC_TIMEOUT ; 
 int IBMVFC_FC_ELS ; 
 int /*<<< orphan*/  IBMVFC_MAD_FORMAT ; 
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_INIT_WAIT ; 
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_NONE ; 
 int /*<<< orphan*/  add_timer (TYPE_6__*) ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (TYPE_6__*) ; 
 scalar_t__ disc_threads ; 
 struct ibmvfc_event* ibmvfc_get_event (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  ibmvfc_init_event (struct ibmvfc_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_init_passthru (struct ibmvfc_event*) ; 
 int /*<<< orphan*/  ibmvfc_release_tgt ; 
 scalar_t__ ibmvfc_send_event (struct ibmvfc_event*,struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_set_tgt_action (struct ibmvfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_tgt_adisc_done ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mod_timer (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  tgt_dbg (struct ibmvfc_target*,char*) ; 
 scalar_t__ timer_pending (TYPE_6__*) ; 

__attribute__((used)) static void ibmvfc_tgt_adisc(struct ibmvfc_target *tgt)
{
	struct ibmvfc_passthru_mad *mad;
	struct ibmvfc_host *vhost = tgt->vhost;
	struct ibmvfc_event *evt;

	if (vhost->discovery_threads >= disc_threads)
		return;

	kref_get(&tgt->kref);
	evt = ibmvfc_get_event(vhost);
	vhost->discovery_threads++;
	ibmvfc_init_event(evt, ibmvfc_tgt_adisc_done, IBMVFC_MAD_FORMAT);
	evt->tgt = tgt;

	ibmvfc_init_passthru(evt);
	mad = &evt->iu.passthru;
	mad->iu.flags = cpu_to_be32(IBMVFC_FC_ELS);
	mad->iu.scsi_id = cpu_to_be64(tgt->scsi_id);
	mad->iu.cancel_key = cpu_to_be32(tgt->cancel_key);

	mad->fc_iu.payload[0] = cpu_to_be32(IBMVFC_ADISC);
	memcpy(&mad->fc_iu.payload[2], &vhost->login_buf->resp.port_name,
	       sizeof(vhost->login_buf->resp.port_name));
	memcpy(&mad->fc_iu.payload[4], &vhost->login_buf->resp.node_name,
	       sizeof(vhost->login_buf->resp.node_name));
	mad->fc_iu.payload[6] = cpu_to_be32(be64_to_cpu(vhost->login_buf->resp.scsi_id) & 0x00ffffff);

	if (timer_pending(&tgt->timer))
		mod_timer(&tgt->timer, jiffies + (IBMVFC_ADISC_TIMEOUT * HZ));
	else {
		tgt->timer.expires = jiffies + (IBMVFC_ADISC_TIMEOUT * HZ);
		add_timer(&tgt->timer);
	}

	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_INIT_WAIT);
	if (ibmvfc_send_event(evt, vhost, IBMVFC_ADISC_PLUS_CANCEL_TIMEOUT)) {
		vhost->discovery_threads--;
		del_timer(&tgt->timer);
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
		kref_put(&tgt->kref, ibmvfc_release_tgt);
	} else
		tgt_dbg(tgt, "Sent ADISC\n");
}