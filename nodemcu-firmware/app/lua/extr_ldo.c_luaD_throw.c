#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  status; TYPE_9__* errorJmp; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_14__ {int status; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* panic ) (TYPE_1__*) ;} ;

/* Variables and functions */
 TYPE_10__* G (TYPE_1__*) ; 
 int /*<<< orphan*/  LUAI_THROW (TYPE_1__*,TYPE_9__*) ; 
 int /*<<< orphan*/  cast_byte (int) ; 
 int /*<<< orphan*/  lua_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  resetstack (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  unfixedstack (TYPE_1__*) ; 
 int /*<<< orphan*/  unset_block_gc (TYPE_1__*) ; 

void luaD_throw (lua_State *L, int errcode) {
  unfixedstack(L); /* make sure the fixedstack & block_gc flags get reset. */
  unset_block_gc(L);
  if (L->errorJmp) {
    L->errorJmp->status = errcode;
    LUAI_THROW(L, L->errorJmp);
  }
  else {
    L->status = cast_byte(errcode);
    if (G(L)->panic) {
      resetstack(L, errcode);
      lua_unlock(L);
      G(L)->panic(L);
    }
    // c_exit(EXIT_FAILURE);
  }
}