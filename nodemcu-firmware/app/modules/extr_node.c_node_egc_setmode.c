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
 unsigned int EGC_ALWAYS ; 
 unsigned int EGC_ON_ALLOC_FAILURE ; 
 unsigned int EGC_ON_MEM_LIMIT ; 
 int /*<<< orphan*/  legc_set_mode (int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_optinteger (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int node_egc_setmode(lua_State* L) {
  unsigned mode  = luaL_checkinteger(L, 1);
  int limit = luaL_optinteger (L, 2, 0);

  luaL_argcheck(L, mode <= (EGC_ON_ALLOC_FAILURE | EGC_ON_MEM_LIMIT | EGC_ALWAYS), 1, "invalid mode");
  luaL_argcheck(L, !(mode & EGC_ON_MEM_LIMIT) || limit!=0, 1, "limit must be non-zero");

  legc_set_mode( L, mode, limit );
  return 0;
}