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
struct Smain {char** argv; int status; int argc; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_GCRESTART ; 
 int /*<<< orphan*/  LUA_GCSTOP ; 
 int collectargs (char**,int*,int*,int*) ; 
 int /*<<< orphan*/ * globalL ; 
 int handle_luainit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_openlibs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_gc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 char* progname ; 
 int runargs (int /*<<< orphan*/ *,char**,int) ; 

__attribute__((used)) static int pmain (lua_State *L) {
  struct Smain *s = (struct Smain *)lua_touserdata(L, 1);
  char **argv = s->argv;
  int script;
  int has_i = 0, has_v = 0, has_e = 0;
  globalL = L;
  if (argv[0] && argv[0][0]) progname = argv[0];
  lua_gc(L, LUA_GCSTOP, 0);  /* stop collector during initialization */
  luaL_openlibs(L);  /* open libraries */
  lua_gc(L, LUA_GCRESTART, 0);
  print_version(L);
  s->status = handle_luainit(L);
  script = collectargs(argv, &has_i, &has_v, &has_e);
  if (script < 0) {  /* invalid args? */
    s->status = 1;
    return 0;
  }
  s->status = runargs(L, argv, (script > 0) ? script : s->argc);
  if (s->status != 0) return 0;
  return 0;
}