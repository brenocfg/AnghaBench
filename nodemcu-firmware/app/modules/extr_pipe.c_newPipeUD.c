#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {scalar_t__ end; scalar_t__ start; } ;
typedef  TYPE_1__ buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  LROT_TABLEREF (int /*<<< orphan*/ ) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushrotable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pipe_meta ; 

__attribute__((used)) static buffer_t *newPipeUD(lua_State *L, int ndx, int n) {   // [-0,+0,-]
  buffer_t *ud = (buffer_t *) lua_newuserdata(L, sizeof(buffer_t));
  lua_pushrotable(L, LROT_TABLEREF(pipe_meta));         /* push the metatable */
	lua_setmetatable(L, -2);                /* set UD's metabtable to pipe_meta */
	ud->start = ud->end = 0;
  lua_rawseti(L, ndx, n);                                 /* T[#T+1] = new UD */
  return ud;                                        /* ud points to new T[#T] */
}