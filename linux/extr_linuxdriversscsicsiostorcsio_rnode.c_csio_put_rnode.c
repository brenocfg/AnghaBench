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
struct csio_rnode {int dummy; } ;
struct csio_lnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DB_ASSERT (int) ; 
 int /*<<< orphan*/  csio_free_rnode (struct csio_rnode*) ; 
 scalar_t__ csio_is_rnode_uninit (struct csio_rnode*) ; 

void
csio_put_rnode(struct csio_lnode *ln, struct csio_rnode *rn)
{
	CSIO_DB_ASSERT(csio_is_rnode_uninit(rn) != 0);
	csio_free_rnode(rn);
}