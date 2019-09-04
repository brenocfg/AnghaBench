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
struct TYPE_6__ {void* addr; } ;
typedef  TYPE_1__ ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 int /*<<< orphan*/  igmp_joingroup (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  igmp_leavegroup (TYPE_1__*,TYPE_1__*) ; 
 void* ipaddr_addr (char const*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ stricmp (char const*,char*) ; 

__attribute__((used)) static int net_multicastJoinLeave( lua_State *L, int join) {
	  size_t il;
	  ip_addr_t multicast_addr;
	  ip_addr_t if_addr;
	  const char *multicast_ip;
	  const char *if_ip;

	  NODE_DBG("net_multicastJoin is called.\n");
	  if(! lua_isstring(L,1) ) return luaL_error( L, "wrong arg type" );
	  if_ip = luaL_checklstring( L, 1, &il );
	  if (if_ip != NULL)
		 if ( if_ip[0] == '\0' || stricmp(if_ip,"any") == 0)
	     {
			 if_ip = "0.0.0.0";
			 il = 7;
	     }
	  if (if_ip == NULL || il > 15 || il < 7) return luaL_error( L, "invalid if ip" );
	  if_addr.addr = ipaddr_addr(if_ip);

	  if(! lua_isstring(L,2) ) return luaL_error( L, "wrong arg type" );
	  multicast_ip = luaL_checklstring( L, 2, &il );
	  if (multicast_ip == NULL || il > 15 || il < 7) return luaL_error( L, "invalid multicast ip" );
	  multicast_addr.addr = ipaddr_addr(multicast_ip);
	  if (join)
	  {
		  igmp_joingroup(&if_addr, &multicast_addr);
	  }
	  else
	  {
		  igmp_leavegroup(&if_addr, &multicast_addr);
	  }
	  return 0;
}