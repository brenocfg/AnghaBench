#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int wcnt; int /*<<< orphan*/ * words; TYPE_2__* dbg; } ;
typedef  TYPE_1__ mrdb_state ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_5__ {scalar_t__ xphase; int /*<<< orphan*/  xm; int /*<<< orphan*/  ccnt; } ;
typedef  TYPE_2__ mrb_debug_context ;
typedef  int /*<<< orphan*/  dbgcmd_state ;

/* Variables and functions */
 int /*<<< orphan*/  DBGST_CONTINUE ; 
 scalar_t__ DBG_PHASE_AFTER_RUN ; 
 int /*<<< orphan*/  DBG_QUIT ; 
 int /*<<< orphan*/  DBG_RUN ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ ,char*,int*) ; 

dbgcmd_state
dbgcmd_continue(mrb_state *mrb, mrdb_state *mrdb)
{
  mrb_debug_context *dbg = mrdb->dbg;
  int ccnt = 1;

  if (mrdb->wcnt > 1){
    sscanf(mrdb->words[1], "%d", &ccnt);
  }
  dbg->ccnt = (uint16_t)(ccnt > 0 ? ccnt : 1);  /* count of continue */

  if (dbg->xphase == DBG_PHASE_AFTER_RUN){
    puts("The program is not running.");
    dbg->xm = DBG_QUIT;
  }
  else {
    dbg->xm = DBG_RUN;
  }
  return DBGST_CONTINUE;
}