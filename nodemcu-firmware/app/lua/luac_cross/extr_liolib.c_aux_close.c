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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int pushresult (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/ ** tofilep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aux_close (lua_State *L) {
  FILE **p = tofilep(L);
  if(*p == stdin || *p == stdout || *p == stderr)
  {
    lua_pushnil(L);
    lua_pushliteral(L, "cannot close standard file");
    return 2;
  }
  int ok = (fclose(*p) == 0);
  *p = NULL;
  return pushresult(L, ok, NULL);
}