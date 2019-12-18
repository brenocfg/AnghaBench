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
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ LUA_TDEADKEY ; 
 int /*<<< orphan*/  gkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gval (int /*<<< orphan*/ *) ; 
 scalar_t__ iscollectable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setttype (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ttisnil (int /*<<< orphan*/ ) ; 
 scalar_t__ ttype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void removeentry (Node *n) {
  lua_assert(ttisnil(gval(n)));
  if (ttype(gkey(n)) != LUA_TDEADKEY && iscollectable(gkey(n)))
//  The gkey is always in RAM so it can be marked as DEAD even though it
//  refers to an LFS object.
    setttype(gkey(n), LUA_TDEADKEY);  /* dead key; remove it */
}