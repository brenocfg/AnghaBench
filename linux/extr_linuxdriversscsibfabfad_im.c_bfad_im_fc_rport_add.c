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
struct fc_rport_identifiers {int /*<<< orphan*/  roles; int /*<<< orphan*/  port_id; void* port_name; void* node_name; } ;
struct fc_rport {int scsi_target_id; int /*<<< orphan*/  channel; struct bfad_itnim_data_s* dd_data; int /*<<< orphan*/  supported_classes; int /*<<< orphan*/  maxframe_size; } ;
struct bfad_itnim_s {int scsi_tgt_id; int /*<<< orphan*/  channel; int /*<<< orphan*/  fcs_itnim; struct fc_rport* fc_rport; } ;
struct bfad_itnim_data_s {struct bfad_itnim_s* itnim; } ;
struct bfad_im_port_s {int /*<<< orphan*/  shost; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_RPORT_ROLE_FCP_TARGET ; 
 int /*<<< orphan*/  FC_RPORT_ROLE_UNKNOWN ; 
 int MAX_FCP_TARGET ; 
 int /*<<< orphan*/  bfa_fcs_itnim_get_cos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_get_fcid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_get_maxfrsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_get_nwwn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_get_pwwn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_hton3b (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 struct fc_rport* fc_remote_port_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fc_rport_identifiers*) ; 
 int /*<<< orphan*/  fc_remote_port_rolechg (struct fc_rport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfad_im_fc_rport_add(struct bfad_im_port_s *im_port, struct bfad_itnim_s *itnim)
{
	struct fc_rport_identifiers rport_ids;
	struct fc_rport *fc_rport;
	struct bfad_itnim_data_s *itnim_data;

	rport_ids.node_name =
		cpu_to_be64(bfa_fcs_itnim_get_nwwn(&itnim->fcs_itnim));
	rport_ids.port_name =
		cpu_to_be64(bfa_fcs_itnim_get_pwwn(&itnim->fcs_itnim));
	rport_ids.port_id =
		bfa_hton3b(bfa_fcs_itnim_get_fcid(&itnim->fcs_itnim));
	rport_ids.roles = FC_RPORT_ROLE_UNKNOWN;

	itnim->fc_rport = fc_rport =
		fc_remote_port_add(im_port->shost, 0, &rport_ids);

	if (!fc_rport)
		return;

	fc_rport->maxframe_size =
		bfa_fcs_itnim_get_maxfrsize(&itnim->fcs_itnim);
	fc_rport->supported_classes = bfa_fcs_itnim_get_cos(&itnim->fcs_itnim);

	itnim_data = fc_rport->dd_data;
	itnim_data->itnim = itnim;

	rport_ids.roles |= FC_RPORT_ROLE_FCP_TARGET;

	if (rport_ids.roles != FC_RPORT_ROLE_UNKNOWN)
		fc_remote_port_rolechg(fc_rport, rport_ids.roles);

	if ((fc_rport->scsi_target_id != -1)
	    && (fc_rport->scsi_target_id < MAX_FCP_TARGET))
		itnim->scsi_tgt_id = fc_rport->scsi_target_id;

	itnim->channel = fc_rport->channel;

	return;
}