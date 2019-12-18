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
struct TYPE_4__ {int log_rw; } ;
struct TYPE_3__ {int /*<<< orphan*/  mute; int /*<<< orphan*/  verbosity; } ;
struct context {TYPE_2__ c2; TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_LINK_ERRORS ; 
 scalar_t__ D_LOG_RW ; 
 int /*<<< orphan*/  D_READ_WRITE ; 
 unsigned int IVM_LEVEL_1 ; 
 unsigned int IVM_LEVEL_2 ; 
 int /*<<< orphan*/  SDL_CONSTRAIN ; 
 scalar_t__ check_debug_level (scalar_t__) ; 
 int /*<<< orphan*/  set_check_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_debug_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mute_cutoff (int /*<<< orphan*/ ) ; 

void
init_verb_mute(struct context *c, unsigned int flags)
{
    if (flags & IVM_LEVEL_1)
    {
        /* set verbosity and mute levels */
        set_check_status(D_LINK_ERRORS, D_READ_WRITE);
        set_debug_level(c->options.verbosity, SDL_CONSTRAIN);
        set_mute_cutoff(c->options.mute);
    }

    /* special D_LOG_RW mode */
    if (flags & IVM_LEVEL_2)
    {
        c->c2.log_rw = (check_debug_level(D_LOG_RW) && !check_debug_level(D_LOG_RW + 1));
    }
}