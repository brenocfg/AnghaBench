#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dao {int /*<<< orphan*/  ctrl_blk; TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dao_get_spos ) (int /*<<< orphan*/ ,unsigned int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int dao_spdif_get_spos(struct dao *dao, unsigned int *spos)
{
	dao->hw->dao_get_spos(dao->ctrl_blk, spos);
	return 0;
}