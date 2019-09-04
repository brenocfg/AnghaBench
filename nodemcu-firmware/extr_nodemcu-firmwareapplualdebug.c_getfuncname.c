#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_11__ {TYPE_1__* p; } ;
struct TYPE_13__ {TYPE_2__ l; } ;
struct TYPE_12__ {scalar_t__ tailcalls; } ;
struct TYPE_10__ {int /*<<< orphan*/ * code; } ;
typedef  int /*<<< orphan*/  Instruction ;
typedef  TYPE_3__ CallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  GETARG_A (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_OPCODE (int /*<<< orphan*/ ) ; 
 scalar_t__ OP_CALL ; 
 scalar_t__ OP_TAILCALL ; 
 scalar_t__ OP_TFORLOOP ; 
 TYPE_8__* ci_func (TYPE_3__*) ; 
 size_t currentpc (int /*<<< orphan*/ *,TYPE_3__*) ; 
 char const* getobjname (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ isLua (TYPE_3__*) ; 

__attribute__((used)) static const char *getfuncname (lua_State *L, CallInfo *ci, const char **name) {
  Instruction i;
  if ((isLua(ci) && ci->tailcalls > 0) || !isLua(ci - 1))
    return NULL;  /* calling function is not Lua (or is unknown) */
  ci--;  /* calling function */
  i = ci_func(ci)->l.p->code[currentpc(L, ci)];
  if (GET_OPCODE(i) == OP_CALL || GET_OPCODE(i) == OP_TAILCALL ||
      GET_OPCODE(i) == OP_TFORLOOP)
    return getobjname(L, ci, GETARG_A(i), name);
  else
    return NULL;  /* no useful name can be found */
}