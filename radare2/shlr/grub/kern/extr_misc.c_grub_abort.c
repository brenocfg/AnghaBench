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
 int /*<<< orphan*/  grub_getkey () ; 
 int /*<<< orphan*/  grub_printf (char*) ; 
 scalar_t__ grub_term_inputs ; 

void
grub_abort (void)
{
  grub_printf ("\nAborted.");

#ifndef GRUB_UTIL
  if (grub_term_inputs)
#endif
    {
      grub_printf (" Press any key to exit.");
      grub_getkey ();
    }

  //grub_exit ();
}