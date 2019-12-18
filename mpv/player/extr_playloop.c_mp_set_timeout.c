#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct MPContext {double sleeptime; int /*<<< orphan*/  dispatch; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_add_timeout (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  mp_dispatch_adjust_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_time_us () ; 

void mp_set_timeout(struct MPContext *mpctx, double sleeptime)
{
    if (mpctx->sleeptime > sleeptime) {
        mpctx->sleeptime = sleeptime;
        int64_t abstime = mp_add_timeout(mp_time_us(), sleeptime);
        mp_dispatch_adjust_timeout(mpctx->dispatch, abstime);
    }
}