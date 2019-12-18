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
typedef  int /*<<< orphan*/  TString ;

/* Variables and functions */
 size_t LUAI_MAXSHORTLEN ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  getstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * internshrstr (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  luaM_toobig (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * luaS_createlngstrobj (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 

TString *luaS_newlstr (lua_State *L, const char *str, size_t l) {
  if (l <= LUAI_MAXSHORTLEN)  /* short string? */
    return internshrstr(L, str, l);
  else {
    TString *ts;
    if (l >= (MAX_SIZE - sizeof(TString))/sizeof(char))
      luaM_toobig(L);
    ts = luaS_createlngstrobj(L, l);
    memcpy(getstr(ts), str, l * sizeof(char));
    return ts;
  }
}