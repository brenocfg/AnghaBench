#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  expdesc ;
struct TYPE_18__ {TYPE_1__* f; } ;
struct TYPE_17__ {int /*<<< orphan*/  linenumber; } ;
struct TYPE_16__ {int linedefined; int /*<<< orphan*/  lastlinedefined; } ;
typedef  TYPE_2__ LexState ;
typedef  TYPE_3__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  TK_END ; 
 int /*<<< orphan*/  TK_FUNCTION ; 
 int /*<<< orphan*/  adjustlocalvars (TYPE_2__*,int) ; 
 int /*<<< orphan*/  check_match (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  checknext (TYPE_2__*,char) ; 
 int /*<<< orphan*/  chunk (TYPE_2__*) ; 
 int /*<<< orphan*/  close_func (TYPE_2__*) ; 
 int /*<<< orphan*/  new_localvarliteral (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_func (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  parlist (TYPE_2__*) ; 
 int /*<<< orphan*/  pushclosure (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void body (LexState *ls, expdesc *e, int needself, int line) {
  /* body ->  `(' parlist `)' chunk END */
  FuncState new_fs;
  open_func(ls, &new_fs);
  new_fs.f->linedefined = line;
  checknext(ls, '(');
  if (needself) {
    new_localvarliteral(ls, "self", 0);
    adjustlocalvars(ls, 1);
  }
  parlist(ls);
  checknext(ls, ')');
  chunk(ls);
  new_fs.f->lastlinedefined = ls->linenumber;
  check_match(ls, TK_END, TK_FUNCTION, line);
  close_func(ls);
  pushclosure(ls, &new_fs, e);
}