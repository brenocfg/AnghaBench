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
typedef  size_t uint16_t ;
struct tcm_qla2xxx_nacl {struct fc_port* fc_port; } ;
struct tcm_qla2xxx_lport {scalar_t__ lport_loopid_map; } ;
struct tcm_qla2xxx_fc_loopid {struct se_node_acl* se_nacl; } ;
struct se_session {int dummy; } ;
struct se_node_acl {int /*<<< orphan*/  initiatorname; } ;
struct fc_port {struct se_session* se_sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static void tcm_qla2xxx_set_sess_by_loop_id(
	struct tcm_qla2xxx_lport *lport,
	struct se_node_acl *new_se_nacl,
	struct tcm_qla2xxx_nacl *nacl,
	struct se_session *se_sess,
	struct fc_port *fc_port,
	uint16_t loop_id)
{
	struct se_node_acl *saved_nacl;
	struct tcm_qla2xxx_fc_loopid *fc_loopid;

	pr_debug("set_sess_by_loop_id: Using loop_id: 0x%04x\n", loop_id);

	fc_loopid = &((struct tcm_qla2xxx_fc_loopid *)
			lport->lport_loopid_map)[loop_id];

	saved_nacl = fc_loopid->se_nacl;
	if (!saved_nacl) {
		pr_debug("Setting up new fc_loopid->se_nacl to new_se_nacl\n");
		fc_loopid->se_nacl = new_se_nacl;
		if (fc_port->se_sess != se_sess)
			fc_port->se_sess = se_sess;
		if (nacl->fc_port != fc_port)
			nacl->fc_port = fc_port;
		return;
	}

	if (nacl->fc_port) {
		if (new_se_nacl == NULL) {
			pr_debug("Clearing nacl->fc_port and fc_loopid->se_nacl\n");
			fc_loopid->se_nacl = NULL;
			nacl->fc_port = NULL;
			return;
		}

		pr_debug("Replacing existing nacl->fc_port and fc_loopid->se_nacl\n");
		fc_loopid->se_nacl = new_se_nacl;
		if (fc_port->se_sess != se_sess)
			fc_port->se_sess = se_sess;
		if (nacl->fc_port != fc_port)
			nacl->fc_port = fc_port;
		return;
	}

	if (new_se_nacl == NULL) {
		pr_debug("Clearing fc_loopid->se_nacl\n");
		fc_loopid->se_nacl = NULL;
		return;
	}

	pr_debug("Replacing existing fc_loopid->se_nacl w/o active nacl->fc_port\n");
	fc_loopid->se_nacl = new_se_nacl;
	if (fc_port->se_sess != se_sess)
		fc_port->se_sess = se_sess;
	if (nacl->fc_port != fc_port)
		nacl->fc_port = fc_port;

	pr_debug("Setup nacl->fc_port %p by loop_id for se_nacl: %p, initiatorname: %s\n",
	    nacl->fc_port, new_se_nacl, new_se_nacl->initiatorname);
}