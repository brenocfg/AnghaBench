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

/* Variables and functions */
 int /*<<< orphan*/ * replace_stack ; 
 scalar_t__ replace_stack_len ; 
 scalar_t__ replace_stack_nr ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
replace_flush()
{
    vim_free(replace_stack);
    replace_stack = NULL;
    replace_stack_len = 0;
    replace_stack_nr = 0;
}