#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
struct TYPE_9__ {TYPE_1__* dbg; } ;
typedef  TYPE_2__ mrdb_state ;
struct TYPE_10__ {int /*<<< orphan*/  eException_class; } ;
typedef  TYPE_3__ mrb_state ;
typedef  int /*<<< orphan*/  dbgcmd_state ;
struct TYPE_8__ {int xm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGST_PROMPT ; 
#define  DBG_NEXT 130 
 void* DBG_QUIT ; 
#define  DBG_RUN 129 
#define  DBG_STEP 128 
 int EOF ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int getchar () ; 
 struct RClass* mrb_define_class (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (TYPE_3__*,struct RClass*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 

dbgcmd_state
dbgcmd_quit(mrb_state *mrb, mrdb_state *mrdb)
{
  switch (mrdb->dbg->xm) {
  case DBG_RUN:
  case DBG_STEP:
  case DBG_NEXT:
    while (1) {
      char c;
      int buf;

      printf("The program is running.  Exit anyway? (y or n) ");
      fflush(stdout);

      if ((buf = getchar()) == EOF) {
        mrdb->dbg->xm = DBG_QUIT;
        break;
      }
      c = buf;
      while (buf != '\n' && (buf = getchar()) != EOF) ;

      if (c == 'y' || c == 'Y') {
        mrdb->dbg->xm = DBG_QUIT;
        break;
      }
      else if (c == 'n' || c == 'N') {
        break;
      }
      else {
        printf("Please answer y or n.\n");
      }
    }
    break;
  default:
    mrdb->dbg->xm = DBG_QUIT;
    break;
  }

  if (mrdb->dbg->xm == DBG_QUIT) {
    struct RClass *exc;
    exc = mrb_define_class(mrb, "DebuggerExit", mrb->eException_class);
    mrb_raise(mrb, exc, "Exit mrdb.");
  }
  return DBGST_PROMPT;
}