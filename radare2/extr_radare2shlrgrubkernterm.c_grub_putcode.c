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
struct grub_term_output {int (* getxy ) () ;int /*<<< orphan*/  (* putchar ) (char) ;} ;
typedef  char grub_uint32_t ;

/* Variables and functions */
 int stub1 () ; 
 int /*<<< orphan*/  stub2 (char) ; 
 int /*<<< orphan*/  stub3 (char) ; 

void
grub_putcode (grub_uint32_t code, struct grub_term_output *term)
{
  if (code == '\t' && term->getxy)
    {
      int n;

      n = 8 - ((term->getxy () >> 8) & 7);
      while (n--)
	grub_putcode (' ', term);

      return;
    }

  (term->putchar) (code);
  if (code == '\n')
    (term->putchar) ('\r');
}