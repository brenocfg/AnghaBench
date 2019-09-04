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
struct fc_rport {int dummy; } ;
struct csio_rnode {int role; int /*<<< orphan*/  nport_id; struct fc_rport* rport; } ;
struct csio_lnode {int /*<<< orphan*/  num_reg_rnodes; } ;

/* Variables and functions */
 int CSIO_RNFR_INITIATOR ; 
 int CSIO_RNFR_TARGET ; 
 int /*<<< orphan*/  csio_ln_dbg (struct csio_lnode*,char*,int /*<<< orphan*/ ) ; 
 struct csio_lnode* csio_rnode_to_lnode (struct csio_rnode*) ; 
 int /*<<< orphan*/  fc_remote_port_delete (struct fc_rport*) ; 

void
csio_unreg_rnode(struct csio_rnode *rn)
{
	struct csio_lnode *ln = csio_rnode_to_lnode(rn);
	struct fc_rport *rport = rn->rport;

	rn->role &= ~(CSIO_RNFR_INITIATOR | CSIO_RNFR_TARGET);
	fc_remote_port_delete(rport);
	ln->num_reg_rnodes--;

	csio_ln_dbg(ln, "Remote port x%x un-registered\n", rn->nport_id);
}