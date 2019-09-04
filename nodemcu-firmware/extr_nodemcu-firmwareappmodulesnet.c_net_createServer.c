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
struct TYPE_4__ {int timeout; } ;
struct TYPE_5__ {TYPE_1__ server; } ;
typedef  TYPE_2__ lnet_userdata ;

/* Variables and functions */
 int TYPE_TCP ; 
 int /*<<< orphan*/  TYPE_TCP_SERVER ; 
 int TYPE_UDP ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int luaL_optlong (int /*<<< orphan*/ *,int,int) ; 
 TYPE_2__* net_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int net_createUDPSocket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_print_deprecation_note (char*,char*) ; 

int net_createServer( lua_State *L ) {
  int type, timeout;

  type = luaL_optlong(L, 1, TYPE_TCP);
  timeout = luaL_optlong(L, 2, 30);

  if (type == TYPE_UDP) {
    platform_print_deprecation_note("net.createServer with net.UDP type", "in next version");
    return net_createUDPSocket( L );
  }
  if (type != TYPE_TCP) return luaL_error(L, "invalid type");

  lnet_userdata *u = net_create(L, TYPE_TCP_SERVER);
  u->server.timeout = timeout;
  return 1;
}