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
 int /*<<< orphan*/  TYPE_UDP_SOCKET ; 
 int /*<<< orphan*/  net_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int net_createUDPSocket( lua_State *L ) {
  net_create(L, TYPE_UDP_SOCKET);
  return 1;
}