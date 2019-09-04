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
struct MPContext {TYPE_1__* opts; } ;
struct TYPE_2__ {int /*<<< orphan*/  pause; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_pause_state (struct MPContext*,int /*<<< orphan*/ ) ; 

void update_internal_pause_state(struct MPContext *mpctx)
{
    set_pause_state(mpctx, mpctx->opts->pause);
}