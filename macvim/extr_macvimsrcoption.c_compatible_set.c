#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPT_FREE ; 
 int P_VIM ; 
 int P_VI_DEF ; 
 int /*<<< orphan*/  didset_options () ; 
 int /*<<< orphan*/  istermoption (TYPE_1__*) ; 
 TYPE_1__* options ; 
 scalar_t__ p_cp ; 
 int /*<<< orphan*/  set_option_default (int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
compatible_set()
{
    int	    opt_idx;

    for (opt_idx = 0; !istermoption(&options[opt_idx]); opt_idx++)
	if (	   ((options[opt_idx].flags & P_VIM) && p_cp)
		|| (!(options[opt_idx].flags & P_VI_DEF) && !p_cp))
	    set_option_default(opt_idx, OPT_FREE, p_cp);
    didset_options();
}