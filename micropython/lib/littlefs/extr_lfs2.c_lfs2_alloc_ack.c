#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ack; } ;
struct TYPE_7__ {TYPE_2__* cfg; TYPE_1__ free; } ;
typedef  TYPE_3__ lfs2_t ;
struct TYPE_6__ {int /*<<< orphan*/  block_count; } ;

/* Variables and functions */

__attribute__((used)) static void lfs2_alloc_ack(lfs2_t *lfs2) {
    lfs2->free.ack = lfs2->cfg->block_count;
}