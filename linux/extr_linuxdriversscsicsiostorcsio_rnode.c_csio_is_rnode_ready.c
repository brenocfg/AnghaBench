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

/* Variables and functions */
 int csio_match_state (struct csio_rnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_rns_ready ; 

int
csio_is_rnode_ready(struct csio_rnode *rn)
{
	return csio_match_state(rn, csio_rns_ready);
}