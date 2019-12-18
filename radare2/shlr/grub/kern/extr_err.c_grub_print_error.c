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
 scalar_t__ GRUB_ERR_NONE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  grub_err_printf (char*,...) ; 
 int /*<<< orphan*/  grub_errmsg ; 
 scalar_t__ grub_errno ; 
 scalar_t__ grub_error_pop () ; 
 scalar_t__ grub_error_stack_assert ; 

void
grub_print_error (void)
{
  /* Print error messages in reverse order. First print active error message
     and then empty error stack.  */
  do
    {
      if (grub_errno != GRUB_ERR_NONE)
        grub_err_printf (_("error: %s.\n"), grub_errmsg);
    }
  while (grub_error_pop ());

  /* If there was an assert while using error stack, report about it.  */
  if (grub_error_stack_assert)
    {
      grub_err_printf ("assert: error stack overflow detected!\n");
      grub_error_stack_assert = 0;
    }
}