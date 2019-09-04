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
struct TYPE_2__ {scalar_t__ b_p_cin; } ;

/* Variables and functions */
 TYPE_1__* curbuf ; 
 int /*<<< orphan*/  p_paste ; 

__attribute__((used)) static int
cindent_on()
{
    return (!p_paste && (curbuf->b_p_cin
# ifdef FEAT_EVAL
		    || *curbuf->b_p_inde != NUL
# endif
		    ));
}