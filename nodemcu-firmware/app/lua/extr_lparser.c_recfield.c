#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct ConsControl {TYPE_4__* t; int /*<<< orphan*/  nh; } ;
typedef  int /*<<< orphan*/  expdesc ;
struct TYPE_20__ {int freereg; } ;
struct TYPE_15__ {scalar_t__ token; } ;
struct TYPE_19__ {TYPE_1__ t; TYPE_6__* fs; } ;
struct TYPE_16__ {int /*<<< orphan*/  info; } ;
struct TYPE_17__ {TYPE_2__ s; } ;
struct TYPE_18__ {TYPE_3__ u; } ;
typedef  TYPE_5__ LexState ;
typedef  TYPE_6__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_INT ; 
 int /*<<< orphan*/  OP_SETTABLE ; 
 scalar_t__ TK_NAME ; 
 int /*<<< orphan*/  checkname (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checknext (TYPE_5__*,char) ; 
 int /*<<< orphan*/  expr (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_codeABC (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int luaK_exp2RK (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaY_checklimit (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  yindex (TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void recfield (LexState *ls, struct ConsControl *cc) {
  /* recfield -> (NAME | `['exp1`]') = exp1 */
  FuncState *fs = ls->fs;
  int reg = ls->fs->freereg;
  expdesc key, val;
  int rkkey;
  if (ls->t.token == TK_NAME) {
    luaY_checklimit(fs, cc->nh, MAX_INT, "items in a constructor");
    checkname(ls, &key);
  }
  else  /* ls->t.token == '[' */
    yindex(ls, &key);
  cc->nh++;
  checknext(ls, '=');
  rkkey = luaK_exp2RK(fs, &key);
  expr(ls, &val);
  luaK_codeABC(fs, OP_SETTABLE, cc->t->u.s.info, rkkey, luaK_exp2RK(fs, &val));
  fs->freereg = reg;  /* free registers */
}