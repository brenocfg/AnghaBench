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
struct csio_lnode {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_LNE_DOWN_LINK ; 
 int CSIO_LNF_LINK_ENABLE ; 
 int /*<<< orphan*/  csio_fcoe_enable_link (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ csio_is_phys_ln (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_ln_dbg (struct csio_lnode*,char*,struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_post_event_lns (struct csio_lnode*,int /*<<< orphan*/ ) ; 

void
csio_lnode_stop(struct csio_lnode *ln)
{
	csio_post_event_lns(ln, CSIO_LNE_DOWN_LINK);
	if (csio_is_phys_ln(ln) && (ln->flags & CSIO_LNF_LINK_ENABLE)) {
		csio_fcoe_enable_link(ln, 0);
		ln->flags &= ~CSIO_LNF_LINK_ENABLE;
	}
	csio_ln_dbg(ln, "stopping ln :%p\n", ln);
}