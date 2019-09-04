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
struct MPContext {int /*<<< orphan*/  dispatch; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_dispatch_interrupt (int /*<<< orphan*/ ) ; 

void mp_wakeup_core(struct MPContext *mpctx)
{
    mp_dispatch_interrupt(mpctx->dispatch);
}