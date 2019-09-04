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
struct tool_mw {int /*<<< orphan*/ * dbgfs_file; scalar_t__ size; scalar_t__ dma_base; int /*<<< orphan*/ * mm_base; } ;
struct tool_ctx {TYPE_2__* ntb; TYPE_1__* peers; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct tool_mw* inmws; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ntb_mw_clear_trans (TYPE_2__*,int,int) ; 

__attribute__((used)) static void tool_free_mw(struct tool_ctx *tc, int pidx, int widx)
{
	struct tool_mw *inmw = &tc->peers[pidx].inmws[widx];

	debugfs_remove(inmw->dbgfs_file);

	if (inmw->mm_base != NULL) {
		ntb_mw_clear_trans(tc->ntb, pidx, widx);
		dma_free_coherent(&tc->ntb->dev, inmw->size,
				  inmw->mm_base, inmw->dma_base);
	}

	inmw->mm_base = NULL;
	inmw->dma_base = 0;
	inmw->size = 0;
	inmw->dbgfs_file = NULL;
}