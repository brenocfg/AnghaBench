#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  isnull; int /*<<< orphan*/  attr; int /*<<< orphan*/  len; int /*<<< orphan*/  entries; int /*<<< orphan*/  dontcare; } ;
struct TYPE_6__ {int /*<<< orphan*/  spl_nright; int /*<<< orphan*/  spl_right; int /*<<< orphan*/  spl_nleft; int /*<<< orphan*/  spl_left; } ;
struct TYPE_7__ {int /*<<< orphan*/  spl_risnull; int /*<<< orphan*/  spl_rattr; TYPE_1__ splitVector; int /*<<< orphan*/  spl_lisnull; int /*<<< orphan*/  spl_lattr; int /*<<< orphan*/  spl_dontcare; } ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  TYPE_2__ GistSplitVector ;
typedef  TYPE_3__ GistSplitUnion ;
typedef  int /*<<< orphan*/  GISTSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  gistunionsubkeyvec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void
gistunionsubkey(GISTSTATE *giststate, IndexTuple *itvec, GistSplitVector *spl)
{
	GistSplitUnion gsvp;

	gsvp.dontcare = spl->spl_dontcare;

	gsvp.entries = spl->splitVector.spl_left;
	gsvp.len = spl->splitVector.spl_nleft;
	gsvp.attr = spl->spl_lattr;
	gsvp.isnull = spl->spl_lisnull;

	gistunionsubkeyvec(giststate, itvec, &gsvp);

	gsvp.entries = spl->splitVector.spl_right;
	gsvp.len = spl->splitVector.spl_nright;
	gsvp.attr = spl->spl_rattr;
	gsvp.isnull = spl->spl_risnull;

	gistunionsubkeyvec(giststate, itvec, &gsvp);
}