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
struct TYPE_2__ {scalar_t__* b_p_inde; } ;

/* Variables and functions */
 scalar_t__ NUL ; 
 TYPE_1__* curbuf ; 
 int /*<<< orphan*/  fixthisline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_c_indent ; 
 int /*<<< orphan*/  get_expr_indent ; 

void
do_c_expr_indent()
{
# ifdef FEAT_EVAL
    if (*curbuf->b_p_inde != NUL)
	fixthisline(get_expr_indent);
    else
# endif
	fixthisline(get_c_indent);
}