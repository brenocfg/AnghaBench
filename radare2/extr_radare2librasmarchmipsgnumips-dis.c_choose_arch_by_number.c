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
struct mips_arch_choice {unsigned long bfd_mach; scalar_t__ bfd_mach_valid; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct mips_arch_choice*) ; 
 struct mips_arch_choice* mips_arch_choices ; 

__attribute__((used)) static const struct mips_arch_choice *
choose_arch_by_number (unsigned long mach)
{
  static unsigned long hint_bfd_mach;
  static const struct mips_arch_choice *hint_arch_choice;
  const struct mips_arch_choice *c;
  unsigned int i;

  /* We optimize this because even if the user specifies no
     flags, this will be done for every instruction!  */
  if (hint_bfd_mach == mach && hint_arch_choice != NULL && hint_arch_choice->bfd_mach == hint_bfd_mach) {
	  return hint_arch_choice;
  }

  for (i = 0, c = NULL; i < ARRAY_SIZE (mips_arch_choices) && !c; i++)
    {
      if (mips_arch_choices[i].bfd_mach_valid
	  && mips_arch_choices[i].bfd_mach == mach)
	{
	  c = &mips_arch_choices[i];
	  hint_bfd_mach = mach;
	  hint_arch_choice = c;
	}
    }
  return c;
}