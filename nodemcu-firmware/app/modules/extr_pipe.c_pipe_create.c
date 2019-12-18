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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LROT_TABLEREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushrotable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pipe_meta ; 

__attribute__((used)) static int pipe_create(lua_State *L) {
  lua_createtable (L, 1, 0);
	lua_pushrotable(L, LROT_TABLEREF(pipe_meta));
	lua_setmetatable(L, 1);              /* set table's metabtable to pipe_meta */
	return 1;                                               /* return the table */
}