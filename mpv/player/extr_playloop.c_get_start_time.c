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
struct MPContext {TYPE_2__* demuxer; TYPE_1__* opts; } ;
struct TYPE_4__ {int /*<<< orphan*/  duration; scalar_t__ start_time; } ;
struct TYPE_3__ {int /*<<< orphan*/  rebase_start_time; } ;

/* Variables and functions */
 scalar_t__ MPMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

double get_start_time(struct MPContext *mpctx, int dir)
{
    double res = 0;
    if (mpctx->demuxer) {
        if (!mpctx->opts->rebase_start_time)
            res += mpctx->demuxer->start_time;
        if (dir < 0)
            res += MPMAX(mpctx->demuxer->duration, 0);
    }
    return res;
}