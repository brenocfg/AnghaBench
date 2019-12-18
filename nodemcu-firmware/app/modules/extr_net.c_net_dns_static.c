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
typedef  int /*<<< orphan*/  ip_addr_t ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_INPROGRESS ; 
 scalar_t__ ERR_OK ; 
 int LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int* calloc (int,int) ; 
 scalar_t__ dns_gethostbyname (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (char const*,int /*<<< orphan*/ *,int*),int*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  luaL_checkanyfunction (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int lwip_lua_checkerr (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  net_dns_static_cb (char const*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int net_dns_static( lua_State* L ) {
  size_t dl;
  const char* domain = luaL_checklstring(L, 1, &dl);
  if (!domain && dl > 128) {
    return luaL_error(L, "wrong domain");
  }

  luaL_checkanyfunction(L, 2);
  lua_pushvalue(L, 2);  // copy argument (func) to the top of stack
  int cbref = luaL_ref(L, LUA_REGISTRYINDEX);
  if (cbref == LUA_NOREF) {
    return luaL_error(L, "wrong callback");
  }
  int *cbref_ptr = calloc(1, sizeof(int));
  cbref_ptr[0] = cbref;
  ip_addr_t addr;
  err_t err = dns_gethostbyname(domain, &addr, net_dns_static_cb, cbref_ptr);
  if (err == ERR_OK) {
    net_dns_static_cb(domain, &addr, cbref_ptr);
    return 0;
  } else if (err == ERR_INPROGRESS) {
    return 0;
  } else {
    int e = lwip_lua_checkerr(L, err);
    free(cbref_ptr);
    return e;
  }
  return 0;
}