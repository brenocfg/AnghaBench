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
struct TYPE_4__ {int /*<<< orphan*/ * b_fname; } ;
struct TYPE_3__ {int /*<<< orphan*/ * w_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SHM_INTRO ; 
 scalar_t__ bufempty () ; 
 TYPE_2__* curbuf ; 
 TYPE_1__* firstwin ; 
 int /*<<< orphan*/  intro_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_shm ; 
 int /*<<< orphan*/ * vim_strchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
maybe_intro_message()
{
    if (bufempty()
	    && curbuf->b_fname == NULL
#ifdef FEAT_WINDOWS
	    && firstwin->w_next == NULL
#endif
	    && vim_strchr(p_shm, SHM_INTRO) == NULL)
	intro_message(FALSE);
}