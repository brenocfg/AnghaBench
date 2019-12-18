#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* smgr_immedsync ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {size_t smgr_which; } ;
typedef  TYPE_1__* SMgrRelation ;
typedef  int /*<<< orphan*/  ForkNumber ;

/* Variables and functions */
 TYPE_3__* smgrsw ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
smgrimmedsync(SMgrRelation reln, ForkNumber forknum)
{
	smgrsw[reln->smgr_which].smgr_immedsync(reln, forknum);
}