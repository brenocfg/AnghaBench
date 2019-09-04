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
struct TYPE_2__ {scalar_t__ type; } ;
struct MPContext {TYPE_1__ current_seek; TYPE_1__ seek; } ;
typedef  enum seek_precision { ____Placeholder_seek_precision } seek_precision ;

/* Variables and functions */
 int /*<<< orphan*/  MPSEEK_ABSOLUTE ; 
 int /*<<< orphan*/  get_current_time (struct MPContext*) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  queue_seek (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void issue_refresh_seek(struct MPContext *mpctx, enum seek_precision min_prec)
{
    // let queued seeks execute at a slightly later point
    if (mpctx->seek.type) {
        mp_wakeup_core(mpctx);
        return;
    }
    // repeat currently ongoing seeks
    if (mpctx->current_seek.type) {
        mpctx->seek = mpctx->current_seek;
        mp_wakeup_core(mpctx);
        return;
    }
    queue_seek(mpctx, MPSEEK_ABSOLUTE, get_current_time(mpctx), min_prec, 0);
}