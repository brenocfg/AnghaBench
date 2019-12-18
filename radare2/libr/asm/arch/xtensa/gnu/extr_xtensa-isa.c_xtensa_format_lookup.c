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
struct TYPE_4__ {int num_formats; TYPE_1__* formats; } ;
typedef  TYPE_2__ xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;
typedef  int xtensa_format ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int XTENSA_UNDEFINED ; 
 scalar_t__ r_str_casecmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xtensa_isa_bad_format ; 
 int /*<<< orphan*/  xtisa_errno ; 
 int /*<<< orphan*/  xtisa_error_msg ; 

xtensa_format
xtensa_format_lookup (xtensa_isa isa, const char *fmtname)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  int fmt;

  if (!fmtname || !*fmtname)
    {
      xtisa_errno = xtensa_isa_bad_format;
      strcpy (xtisa_error_msg, "invalid format name");
      return XTENSA_UNDEFINED;
    }

  for (fmt = 0; fmt < intisa->num_formats; fmt++)
    {
	  if (r_str_casecmp (fmtname, intisa->formats[fmt].name) == 0) {
		  return fmt;
	  }
    }

  xtisa_errno = xtensa_isa_bad_format;
  sprintf (xtisa_error_msg, "format \"%s\" not recognized", fmtname);
  return XTENSA_UNDEFINED;
}