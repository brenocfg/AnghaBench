#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int atxctl; } ;
struct TYPE_4__ {TYPE_1__ bf; } ;
struct daio_mgr_ctrl_blk {TYPE_2__ dirty; int /*<<< orphan*/ * txctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATXCTL_EN ; 
 int /*<<< orphan*/  set_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int daio_mgr_enb_dao(void *blk, unsigned int idx)
{
	struct daio_mgr_ctrl_blk *ctl = blk;

	set_field(&ctl->txctl[idx], ATXCTL_EN, 1);
	ctl->dirty.bf.atxctl |= (0x1 << idx);
	return 0;
}