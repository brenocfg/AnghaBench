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
struct MPContext {TYPE_2__* vo_chain; TYPE_1__* ao_chain; } ;
struct TYPE_4__ {int underrun; } ;
struct TYPE_3__ {int underrun; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 

__attribute__((used)) static void clear_underruns(struct MPContext *mpctx)
{
    if (mpctx->ao_chain && mpctx->ao_chain->underrun) {
        mpctx->ao_chain->underrun = false;
        mp_wakeup_core(mpctx);
    }

    if (mpctx->vo_chain && mpctx->vo_chain->underrun) {
        mpctx->vo_chain->underrun = false;
        mp_wakeup_core(mpctx);
    }
}