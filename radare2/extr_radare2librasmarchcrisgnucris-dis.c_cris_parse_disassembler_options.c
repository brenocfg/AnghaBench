#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cris_disasm_data {int trace_case; int distype; } ;
typedef  enum cris_disass_family { ____Placeholder_cris_disass_family } cris_disass_family ;
struct TYPE_3__ {int /*<<< orphan*/  disassembler_options; scalar_t__ private_data; } ;
typedef  TYPE_1__ disassemble_info ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

bfd_boolean
cris_parse_disassembler_options (disassemble_info *info,
				 enum cris_disass_family distype)
{
  struct cris_disasm_data *disdata = (struct cris_disasm_data *) info->private_data;
  if (!disdata) {
	  return FALSE;
  }

  info->private_data = calloc (1, sizeof (struct cris_disasm_data));

  /* Default true.  */
  disdata->trace_case
    = (!info->disassembler_options
       || (strcmp (info->disassembler_options, "nocase") != 0));

  disdata->distype = distype;
  return TRUE;
}