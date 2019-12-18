#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int xtensa_regfile ;
struct TYPE_4__ {int num_regfiles; TYPE_1__* regfiles; } ;
typedef  TYPE_2__ xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int XTENSA_UNDEFINED ; 
 int /*<<< orphan*/  filename_cmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xtensa_isa_bad_regfile ; 
 int /*<<< orphan*/  xtisa_errno ; 
 int /*<<< orphan*/  xtisa_error_msg ; 

xtensa_regfile
xtensa_regfile_lookup (xtensa_isa isa, const char *name)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  int n;

  if (!name || !*name)
    {
      xtisa_errno = xtensa_isa_bad_regfile;
      strcpy (xtisa_error_msg, "invalid regfile name");
      return XTENSA_UNDEFINED;
    }

  /* The expected number of regfiles is small; use a linear search.  */
  for (n = 0; n < intisa->num_regfiles; n++)
    {
	  if (!filename_cmp (intisa->regfiles[n].name, name)) {
		  return n;
	  }
    }

  xtisa_errno = xtensa_isa_bad_regfile;
  sprintf (xtisa_error_msg, "regfile \"%s\" not recognized", name);
  return XTENSA_UNDEFINED;
}