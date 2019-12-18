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
 int TYPE_TCP ; 
 int /*<<< orphan*/  TYPE_TCP_CLIENT ; 
 int TYPE_UDP ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int luaL_optlong (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  net_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int net_createUDPSocket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_print_deprecation_note (char*,char*) ; 
 int tls_socket_create (int /*<<< orphan*/ *) ; 

int net_createConnection( lua_State *L ) {
  int type, secure;

  type = luaL_optlong(L, 1, TYPE_TCP);
  secure = luaL_optlong(L, 2, 0);

  if (type == TYPE_UDP) {
    platform_print_deprecation_note("net.createConnection with net.UDP type", "in next version");
    return net_createUDPSocket( L );
  }
  if (type != TYPE_TCP) return luaL_error(L, "invalid type");
  if (secure) {
    platform_print_deprecation_note("net.createConnection with secure flag", "in next version");
#ifdef TLS_MODULE_PRESENT
    return tls_socket_create( L );
#else
    return luaL_error(L, "secure connections not enabled");
#endif
  }
  net_create(L, TYPE_TCP_CLIENT);
  return 1;
}