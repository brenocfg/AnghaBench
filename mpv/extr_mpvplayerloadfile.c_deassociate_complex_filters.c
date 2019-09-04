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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct MPContext {int num_tracks; int /*<<< orphan*/  lavfi_graph; int /*<<< orphan*/  lavfi; TYPE_1__* ao_chain; TYPE_3__* vo_chain; TYPE_2__** tracks; } ;
struct TYPE_6__ {int /*<<< orphan*/ * filter_src; } ;
struct TYPE_5__ {int /*<<< orphan*/ * sink; } ;
struct TYPE_4__ {int /*<<< orphan*/ * filter_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void deassociate_complex_filters(struct MPContext *mpctx)
{
    for (int n = 0; n < mpctx->num_tracks; n++)
        mpctx->tracks[n]->sink = NULL;
    if (mpctx->vo_chain)
        mpctx->vo_chain->filter_src = NULL;
    if (mpctx->ao_chain)
        mpctx->ao_chain->filter_src = NULL;
    TA_FREEP(&mpctx->lavfi);
    TA_FREEP(&mpctx->lavfi_graph);
}