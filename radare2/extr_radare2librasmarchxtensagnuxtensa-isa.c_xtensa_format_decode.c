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
struct TYPE_2__ {scalar_t__ (* format_decode_fn ) (int /*<<< orphan*/  const) ;} ;
typedef  TYPE_1__ xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;
typedef  int /*<<< orphan*/  xtensa_insnbuf ;
typedef  scalar_t__ xtensa_format ;

/* Variables and functions */
 scalar_t__ XTENSA_UNDEFINED ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  xtensa_isa_bad_format ; 
 int /*<<< orphan*/  xtisa_errno ; 
 int /*<<< orphan*/  xtisa_error_msg ; 

xtensa_format
xtensa_format_decode (xtensa_isa isa, const xtensa_insnbuf insn)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  xtensa_format fmt;

  fmt = (intisa->format_decode_fn) (insn);
  if (fmt != XTENSA_UNDEFINED) {
	  return fmt;
  }

  xtisa_errno = xtensa_isa_bad_format;
  strcpy (xtisa_error_msg, "cannot decode instruction format");
  return XTENSA_UNDEFINED;
}