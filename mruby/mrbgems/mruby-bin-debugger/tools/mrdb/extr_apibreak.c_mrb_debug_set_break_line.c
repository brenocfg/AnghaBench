#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_9__ {scalar_t__ bpnum; scalar_t__ next_bpno; TYPE_3__* bp; int /*<<< orphan*/  root_irep; } ;
typedef  TYPE_4__ mrb_debug_context ;
typedef  size_t int32_t ;
struct TYPE_6__ {char* file; scalar_t__ lineno; } ;
struct TYPE_7__ {TYPE_1__ linepoint; } ;
struct TYPE_8__ {scalar_t__ bpno; TYPE_2__ point; int /*<<< orphan*/  type; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 scalar_t__ MAX_BREAKPOINT ; 
 scalar_t__ MAX_BREAKPOINTNO ; 
 int /*<<< orphan*/  MRB_DEBUG_BPTYPE_LINE ; 
 scalar_t__ MRB_DEBUG_BP_FILE_OK ; 
 size_t MRB_DEBUG_BREAK_INVALID_FILE ; 
 size_t MRB_DEBUG_BREAK_INVALID_LINENO ; 
 size_t MRB_DEBUG_BREAK_NO_OVER ; 
 size_t MRB_DEBUG_BREAK_NUM_OVER ; 
 size_t MRB_DEBUG_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ check_file_lineno (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,scalar_t__) ; 

int32_t
mrb_debug_set_break_line(mrb_state *mrb, mrb_debug_context *dbg, const char *file, uint16_t lineno)
{
  int32_t index;
  char* set_file;
  uint16_t result;

  if ((mrb == NULL)||(dbg == NULL)||(file == NULL)) {
    return MRB_DEBUG_INVALID_ARGUMENT;
  }

  if (dbg->bpnum >= MAX_BREAKPOINT) {
    return MRB_DEBUG_BREAK_NUM_OVER;
  }

  if (dbg->next_bpno > MAX_BREAKPOINTNO) {
    return MRB_DEBUG_BREAK_NO_OVER;
  }

  /* file and lineno check (line type mrb_debug_line_ary only.) */
  result = check_file_lineno(mrb, dbg->root_irep, file, lineno);
  if (result == 0) {
    return MRB_DEBUG_BREAK_INVALID_FILE;
  }
  else if (result == MRB_DEBUG_BP_FILE_OK) {
    return MRB_DEBUG_BREAK_INVALID_LINENO;
  }

  set_file = (char*)mrb_malloc(mrb, strlen(file) + 1);

  index = dbg->bpnum;
  dbg->bp[index].bpno = dbg->next_bpno;
  dbg->next_bpno++;
  dbg->bp[index].enable = TRUE;
  dbg->bp[index].type = MRB_DEBUG_BPTYPE_LINE;
  dbg->bp[index].point.linepoint.lineno = lineno;
  dbg->bpnum++;

  strncpy(set_file, file, strlen(file) + 1);

  dbg->bp[index].point.linepoint.file = set_file;

  return dbg->bp[index].bpno;
}