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
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int /*<<< orphan*/ * expr_line ; 
 int /*<<< orphan*/ * vim_strsave (int /*<<< orphan*/ *) ; 

char_u *
get_expr_line_src()
{
    if (expr_line == NULL)
	return NULL;
    return vim_strsave(expr_line);
}