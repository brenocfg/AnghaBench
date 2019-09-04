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
struct bfad_s {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  qos; } ;
struct bfa_rport_aen_data_s {TYPE_3__ priv; } ;
struct bfa_fcs_rport_s {TYPE_7__* fcs; int /*<<< orphan*/  pwwn; struct bfa_fcs_lport_s* port; } ;
struct bfa_fcs_lport_s {TYPE_4__* fabric; TYPE_1__* fcs; } ;
struct TYPE_9__ {int /*<<< orphan*/  qos; } ;
struct TYPE_12__ {int /*<<< orphan*/  rpwwn; void* lpwwn; void* ppwwn; int /*<<< orphan*/  vf_id; TYPE_2__ priv; } ;
struct TYPE_13__ {TYPE_5__ rport; } ;
struct bfa_aen_entry_s {TYPE_6__ aen_data; } ;
typedef  enum bfa_rport_aen_event { ____Placeholder_bfa_rport_aen_event } bfa_rport_aen_event ;
struct TYPE_14__ {int /*<<< orphan*/  fcs_aen_seq; } ;
struct TYPE_11__ {int /*<<< orphan*/  vf_id; } ;
struct TYPE_8__ {scalar_t__ bfad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_AEN_CAT_RPORT ; 
 int BFA_RPORT_AEN_QOS_FLOWID ; 
 int BFA_RPORT_AEN_QOS_PRIO ; 
 struct bfa_fcs_lport_s* bfa_fcs_get_base_port (TYPE_7__*) ; 
 void* bfa_fcs_lport_get_pwwn (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfad_get_aen_entry (struct bfad_s*,struct bfa_aen_entry_s*) ; 
 int /*<<< orphan*/  bfad_im_post_vendor_event (struct bfa_aen_entry_s*,struct bfad_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_rport_aen_post(struct bfa_fcs_rport_s *rport,
			enum bfa_rport_aen_event event,
			struct bfa_rport_aen_data_s *data)
{
	struct bfa_fcs_lport_s *port = rport->port;
	struct bfad_s *bfad = (struct bfad_s *)port->fcs->bfad;
	struct bfa_aen_entry_s  *aen_entry;

	bfad_get_aen_entry(bfad, aen_entry);
	if (!aen_entry)
		return;

	if (event == BFA_RPORT_AEN_QOS_PRIO)
		aen_entry->aen_data.rport.priv.qos = data->priv.qos;
	else if (event == BFA_RPORT_AEN_QOS_FLOWID)
		aen_entry->aen_data.rport.priv.qos = data->priv.qos;

	aen_entry->aen_data.rport.vf_id = rport->port->fabric->vf_id;
	aen_entry->aen_data.rport.ppwwn = bfa_fcs_lport_get_pwwn(
					bfa_fcs_get_base_port(rport->fcs));
	aen_entry->aen_data.rport.lpwwn = bfa_fcs_lport_get_pwwn(rport->port);
	aen_entry->aen_data.rport.rpwwn = rport->pwwn;

	/* Send the AEN notification */
	bfad_im_post_vendor_event(aen_entry, bfad, ++rport->fcs->fcs_aen_seq,
				  BFA_AEN_CAT_RPORT, event);
}