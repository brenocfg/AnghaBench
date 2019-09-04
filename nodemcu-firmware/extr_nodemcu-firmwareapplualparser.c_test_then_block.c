#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  LexState ;

/* Variables and functions */
 int /*<<< orphan*/  TK_THEN ; 
 int /*<<< orphan*/  block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checknext (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cond (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaX_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_then_block (LexState *ls) {
  /* test_then_block -> [IF | ELSEIF] cond THEN block */
  int condexit;
  luaX_next(ls);  /* skip IF or ELSEIF */
  condexit = cond(ls);
  checknext(ls, TK_THEN);
  block(ls);  /* `then' part */
  return condexit;
}