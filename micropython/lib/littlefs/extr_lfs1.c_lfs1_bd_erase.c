#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* cfg; } ;
typedef  TYPE_1__ lfs1_t ;
typedef  int /*<<< orphan*/  lfs1_block_t ;
struct TYPE_5__ {int (* erase ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lfs1_bd_erase(lfs1_t *lfs1, lfs1_block_t block) {
    return lfs1->cfg->erase(lfs1->cfg, block);
}