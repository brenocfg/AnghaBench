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
typedef  int /*<<< orphan*/  lua_State ;
typedef  scalar_t__ lua_Integer ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
struct TYPE_6__ {char const* src_end; } ;
typedef  TYPE_1__ MatchState ;

/* Variables and functions */
 int LUA_TFUNCTION ; 
 int LUA_TNUMBER ; 
 int LUA_TSTRING ; 
 int LUA_TTABLE ; 
 int /*<<< orphan*/  add_value (TYPE_1__*,int /*<<< orphan*/ *,char const*,char const*,int) ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ luaL_optinteger (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,scalar_t__) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 char* match (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  prepstate (TYPE_1__*,int /*<<< orphan*/ *,char const*,size_t,char const*,size_t) ; 
 int /*<<< orphan*/  reprepstate (TYPE_1__*) ; 

__attribute__((used)) static int str_gsub (lua_State *L) {
  size_t srcl, lp;
  const char *src = luaL_checklstring(L, 1, &srcl);  /* subject */
  const char *p = luaL_checklstring(L, 2, &lp);  /* pattern */
  const char *lastmatch = NULL;  /* end of last match */
  int tr = lua_type(L, 3);  /* replacement type */
  lua_Integer max_s = luaL_optinteger(L, 4, srcl + 1);  /* max replacements */
  int anchor = (*p == '^');
  lua_Integer n = 0;  /* replacement count */
  MatchState ms;
  luaL_Buffer b;
  luaL_argcheck(L, tr == LUA_TNUMBER || tr == LUA_TSTRING ||
                   tr == LUA_TFUNCTION || tr == LUA_TTABLE, 3,
                      "string/function/table expected");
  luaL_buffinit(L, &b);
  if (anchor) {
    p++; lp--;  /* skip anchor character */
  }
  prepstate(&ms, L, src, srcl, p, lp);
  while (n < max_s) {
    const char *e;
    reprepstate(&ms);  /* (re)prepare state for new match */
    if ((e = match(&ms, src, p)) != NULL && e != lastmatch) {  /* match? */
      n++;
      add_value(&ms, &b, src, e, tr);  /* add replacement to buffer */
      src = lastmatch = e;
    }
    else if (src < ms.src_end)  /* otherwise, skip one character */
      luaL_addchar(&b, *src++);
    else break;  /* end of subject */
    if (anchor) break;
  }
  luaL_addlstring(&b, src, ms.src_end-src);
  luaL_pushresult(&b);
  lua_pushinteger(L, n);  /* number of substitutions */
  return 2;
}