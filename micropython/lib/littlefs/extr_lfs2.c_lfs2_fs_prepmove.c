#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  gpending; int /*<<< orphan*/  gdelta; } ;
typedef  TYPE_1__ lfs2_t ;
typedef  int /*<<< orphan*/  lfs2_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  lfs2_gstate_xormove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void lfs2_fs_prepmove(lfs2_t *lfs2,
        uint16_t id, const lfs2_block_t pair[2]) {
    lfs2_gstate_xormove(&lfs2->gdelta,   &lfs2->gpending, id, pair);
    lfs2_gstate_xormove(&lfs2->gpending, &lfs2->gpending, id, pair);
}