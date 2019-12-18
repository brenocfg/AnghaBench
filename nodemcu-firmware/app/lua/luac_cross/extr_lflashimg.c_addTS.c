#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ top; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_12__ {scalar_t__ tt; } ;
struct TYPE_14__ {TYPE_1__ tsv; } ;
typedef  TYPE_3__ TString ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINT (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ LUA_TSTRING ; 
 int /*<<< orphan*/  getstr (TYPE_3__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  lua_pushinteger (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lua_pushnil (TYPE_2__*) ; 
 int /*<<< orphan*/  lua_rawset (TYPE_2__*,int) ; 
 int /*<<< orphan*/  setsvalue (TYPE_2__*,scalar_t__,TYPE_3__*) ; 

__attribute__((used)) static void addTS(lua_State *L, TString *ts) {
  lua_assert(ts->tsv.tt==LUA_TSTRING);
  lua_pushnil(L);
  setsvalue(L, L->top-1, ts);
  lua_pushinteger(L, 1);
  lua_rawset(L, -3);
  DBG_PRINT("Adding string: %s\n",getstr(ts));
}