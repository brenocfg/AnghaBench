#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int current; scalar_t__ linenumber; } ;
typedef  TYPE_1__ LexState ;

/* Variables and functions */
 scalar_t__ MAX_INT ; 
 scalar_t__ currIsNewline (TYPE_1__*) ; 
 int /*<<< orphan*/  luaX_syntaxerror (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  lua_assert (scalar_t__) ; 
 int /*<<< orphan*/  next (TYPE_1__*) ; 

__attribute__((used)) static void inclinenumber (LexState *ls) {
  int old = ls->current;
  lua_assert(currIsNewline(ls));
  next(ls);  /* skip `\n' or `\r' */
  if (currIsNewline(ls) && ls->current != old)
    next(ls);  /* skip `\n\r' or `\r\n' */
  if (++ls->linenumber >= MAX_INT)
    luaX_syntaxerror(ls, "chunk has too many lines");
}