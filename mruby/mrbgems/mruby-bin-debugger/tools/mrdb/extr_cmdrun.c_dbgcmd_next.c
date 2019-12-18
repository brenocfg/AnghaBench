#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* dbg; } ;
typedef  TYPE_3__ mrdb_state ;
struct TYPE_10__ {TYPE_2__* c; } ;
typedef  TYPE_4__ mrb_state ;
typedef  int /*<<< orphan*/  dbgcmd_state ;
struct TYPE_8__ {int /*<<< orphan*/  ci; } ;
struct TYPE_7__ {int /*<<< orphan*/  prvci; int /*<<< orphan*/  xm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGST_CONTINUE ; 
 int /*<<< orphan*/  DBG_NEXT ; 

dbgcmd_state
dbgcmd_next(mrb_state *mrb, mrdb_state *mrdb)
{
  mrdb->dbg->xm = DBG_NEXT;
  mrdb->dbg->prvci = mrb->c->ci;
  return DBGST_CONTINUE;
}