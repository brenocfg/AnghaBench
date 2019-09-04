#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pp_ctx {int pmask; int nmask; int /*<<< orphan*/  in_db; TYPE_1__* ntb; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int) ; 
 int GENMASK_ULL (int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 
 int ntb_peer_port_count (TYPE_1__*) ; 
 int ntb_peer_port_number (TYPE_1__*,int) ; 
 int ntb_port_number (TYPE_1__*) ; 

__attribute__((used)) static void pp_init_flds(struct pp_ctx *pp)
{
	int pidx, lport, pcnt;

	/* Find global port index */
	lport = ntb_port_number(pp->ntb);
	pcnt = ntb_peer_port_count(pp->ntb);
	for (pidx = 0; pidx < pcnt; pidx++) {
		if (lport < ntb_peer_port_number(pp->ntb, pidx))
			break;
	}

	pp->in_db = BIT_ULL(pidx);
	pp->pmask = GENMASK_ULL(pidx, 0) >> 1;
	pp->nmask = GENMASK_ULL(pcnt - 1, pidx);

	dev_dbg(&pp->ntb->dev, "Inbound db %#llx, prev %#llx, next %#llx\n",
		pp->in_db, pp->pmask, pp->nmask);
}