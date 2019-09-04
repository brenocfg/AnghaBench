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
struct mesh_state {int n_msgout; int aborting; int /*<<< orphan*/  stat; int /*<<< orphan*/ * msgout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT ; 
 int /*<<< orphan*/  DID_ABORT ; 
 int /*<<< orphan*/  dlog (struct mesh_state*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_abort(struct mesh_state *ms)
{
	ms->msgout[0] = ABORT;
	ms->n_msgout = 1;
	ms->aborting = 1;
	ms->stat = DID_ABORT;
	dlog(ms, "abort", 0);
}