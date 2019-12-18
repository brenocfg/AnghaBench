#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dbg; int /*<<< orphan*/  srcpath; } ;
typedef  TYPE_1__ mrdb_state ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_10__ {char* filename; int /*<<< orphan*/  line_max; int /*<<< orphan*/  line_min; } ;
typedef  TYPE_2__ listcmd_parser_state ;
typedef  int /*<<< orphan*/  dbgcmd_state ;

/* Variables and functions */
 int /*<<< orphan*/  DBGST_PROMPT ; 
 int /*<<< orphan*/  listcmd_parser_state_free (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* listcmd_parser_state_new (int /*<<< orphan*/ *) ; 
 char* mrb_debug_get_source (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_debug_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ parse_listcmd_args (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 

dbgcmd_state
dbgcmd_list(mrb_state *mrb, mrdb_state *mrdb)
{
  char *filename;
  listcmd_parser_state *st = listcmd_parser_state_new(mrb);

  if (parse_listcmd_args(mrb, mrdb, st)) {
    if ((filename = mrb_debug_get_source(mrb, mrdb, mrdb->srcpath, st->filename)) == NULL) {
      filename = st->filename;
    }
    mrb_debug_list(mrb, mrdb->dbg, filename, st->line_min, st->line_max);

    if (filename != NULL && filename != st->filename) {
      mrb_free(mrb, filename);
    }
    listcmd_parser_state_free(mrb, st);
  }

  return DBGST_PROMPT;
}