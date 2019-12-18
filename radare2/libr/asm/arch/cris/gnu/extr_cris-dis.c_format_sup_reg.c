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
typedef  scalar_t__ bfd_boolean ;
struct TYPE_2__ {char* name; unsigned int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  REGISTER_PREFIX_CHAR ; 
 TYPE_1__* cris_support_regs ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
format_sup_reg (unsigned int regno,
		char *outbuffer_start,
		bfd_boolean with_reg_prefix)
{
  char *outbuffer = outbuffer_start;
  int i;

  if (with_reg_prefix) {
	  *outbuffer++ = REGISTER_PREFIX_CHAR;
  }

  for (i = 0; cris_support_regs[i].name != NULL; i++) {
	  if (cris_support_regs[i].number == regno) {
		  sprintf (outbuffer, "%s", cris_support_regs[i].name);
		  return outbuffer_start + strlen (outbuffer_start);
	  }
  }

  /* There's supposed to be register names covering all numbers, though
     some may be generic names.  */
  sprintf (outbuffer, "format_sup_reg-BUG");
  return outbuffer_start + strlen (outbuffer_start);
}