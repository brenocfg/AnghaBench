#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  expdesc ;
struct TYPE_15__ {TYPE_1__* f; } ;
struct TYPE_14__ {int /*<<< orphan*/  envn; } ;
struct TYPE_13__ {int is_vararg; } ;
typedef  TYPE_2__ LexState ;
typedef  TYPE_3__ FuncState ;
typedef  int /*<<< orphan*/  BlockCnt ;

/* Variables and functions */
 int /*<<< orphan*/  TK_EOS ; 
 int /*<<< orphan*/  VLOCAL ; 
 int /*<<< orphan*/  check (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_func (TYPE_2__*) ; 
 int /*<<< orphan*/  init_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaX_next (TYPE_2__*) ; 
 int /*<<< orphan*/  newupvalue (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_func (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  statlist (TYPE_2__*) ; 

__attribute__((used)) static void mainfunc (LexState *ls, FuncState *fs) {
  BlockCnt bl;
  expdesc v;
  open_func(ls, fs, &bl);
  fs->f->is_vararg = 1;  /* main function is always declared vararg */
  init_exp(&v, VLOCAL, 0);  /* create and... */
  newupvalue(fs, ls->envn, &v);  /* ...set environment upvalue */
  luaX_next(ls);  /* read first token */
  statlist(ls);  /* parse main body */
  check(ls, TK_EOS);
  close_func(ls);
}