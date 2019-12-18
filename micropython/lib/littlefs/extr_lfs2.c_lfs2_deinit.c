#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_8__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_11__ {TYPE_4__ free; TYPE_3__* cfg; TYPE_2__ pcache; TYPE_1__ rcache; } ;
typedef  TYPE_5__ lfs2_t ;
struct TYPE_9__ {int /*<<< orphan*/  lookahead_buffer; int /*<<< orphan*/  prog_buffer; int /*<<< orphan*/  read_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  lfs2_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lfs2_deinit(lfs2_t *lfs2) {
    // free allocated memory
    if (!lfs2->cfg->read_buffer) {
        lfs2_free(lfs2->rcache.buffer);
    }

    if (!lfs2->cfg->prog_buffer) {
        lfs2_free(lfs2->pcache.buffer);
    }

    if (!lfs2->cfg->lookahead_buffer) {
        lfs2_free(lfs2->free.buffer);
    }

    return 0;
}