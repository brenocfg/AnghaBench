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
struct TYPE_5__ {scalar_t__ litLengthSum; } ;
struct TYPE_7__ {scalar_t__ dictLimit; } ;
struct TYPE_6__ {int /*<<< orphan*/ * dictMatchState; TYPE_1__ opt; scalar_t__ loadedDictEnd; TYPE_3__ window; scalar_t__ nextToUpdate3; scalar_t__ nextToUpdate; } ;
typedef  TYPE_2__ ZSTD_matchState_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_window_clear (TYPE_3__*) ; 

__attribute__((used)) static void ZSTD_invalidateMatchState(ZSTD_matchState_t* ms)
{
    ZSTD_window_clear(&ms->window);

    ms->nextToUpdate = ms->window.dictLimit + 1;
    ms->nextToUpdate3 = ms->window.dictLimit + 1;
    ms->loadedDictEnd = 0;
    ms->opt.litLengthSum = 0;  /* force reset of btopt stats */
    ms->dictMatchState = NULL;
}