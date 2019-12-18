#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {scalar_t__ level; scalar_t__ nlevels; TYPE_1__* stack; } ;
struct TYPE_4__ {scalar_t__ offset; int /*<<< orphan*/  size; int /*<<< orphan*/  lua_object_ref; } ;
typedef  TYPE_1__ ENC_DATA_STATE ;
typedef  TYPE_2__ ENC_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_ref (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sjson_encoder_get_table_size (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void enc_push_stack(lua_State *L, ENC_DATA *data, int argno) {
  if (++data->level >= data->nlevels) {
    luaL_error(L, "encoder stack overflow");
  }
  lua_pushvalue(L, argno);
  ENC_DATA_STATE *state = &data->stack[data->level];
  state->lua_object_ref = lua_ref(L, 1);
  state->size = sjson_encoder_get_table_size(L, argno);
  state->offset = 0;         // We haven't started on this one yet
}