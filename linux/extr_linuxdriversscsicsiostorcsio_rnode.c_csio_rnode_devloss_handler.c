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
struct csio_rnode {int /*<<< orphan*/  sm; } ;
struct csio_lnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_RNFE_CLOSE ; 
 scalar_t__ csio_is_rnode_ready (struct csio_rnode*) ; 
 scalar_t__ csio_is_rnode_uninit (struct csio_rnode*) ; 
 int /*<<< orphan*/  csio_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_put_rnode (struct csio_lnode*,struct csio_rnode*) ; 
 struct csio_lnode* csio_rnode_to_lnode (struct csio_rnode*) ; 

void
csio_rnode_devloss_handler(struct csio_rnode *rn)
{
	struct csio_lnode *ln = csio_rnode_to_lnode(rn);

	/* ignore if same rnode came back as online */
	if (csio_is_rnode_ready(rn))
		return;

	csio_post_event(&rn->sm, CSIO_RNFE_CLOSE);

	/* Free rn if in uninit state */
	if (csio_is_rnode_uninit(rn))
		csio_put_rnode(ln, rn);
}