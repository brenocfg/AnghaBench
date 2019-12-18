#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char current; int /*<<< orphan*/  buff; int /*<<< orphan*/  decpoint; } ;
struct TYPE_11__ {int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ SemInfo ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  buffreplace (TYPE_2__*,char,int /*<<< orphan*/ ) ; 
 scalar_t__ check_next (TYPE_2__*,char*) ; 
 scalar_t__ isalnum (char) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  luaO_str2d (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaZ_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (scalar_t__) ; 
 int /*<<< orphan*/  save (TYPE_2__*,char) ; 
 int /*<<< orphan*/  save_and_next (TYPE_2__*) ; 
 int /*<<< orphan*/  trydecpoint (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void read_numeral (LexState *ls, SemInfo *seminfo) {
  lua_assert(isdigit(ls->current));
  do {
    save_and_next(ls);
  } while (isdigit(ls->current) || ls->current == '.');
  if (check_next(ls, "Ee"))  /* `E'? */
    check_next(ls, "+-");  /* optional exponent sign */
  while (isalnum(ls->current) || ls->current == '_')
    save_and_next(ls);
  save(ls, '\0');
  buffreplace(ls, '.', ls->decpoint);  /* follow locale for decimal point */
  if (!luaO_str2d(luaZ_buffer(ls->buff), &seminfo->r))  /* format error? */
    trydecpoint(ls, seminfo); /* try to update decimal point separator */
}