#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ addr; } ;
struct ip_info {TYPE_1__ gw; TYPE_1__ netmask; TYPE_1__ ip; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int IP2STR (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  wifi_get_ip_info (int /*<<< orphan*/ ,struct ip_info*) ; 

__attribute__((used)) static int wifi_getip( lua_State* L, uint8_t mode )
{
  struct ip_info pTempIp;
  char temp[64];
  wifi_get_ip_info(mode, &pTempIp);
  if(pTempIp.ip.addr==0){
    lua_pushnil(L);
    return 1;
  }
  else
  {
    sprintf(temp, "%d.%d.%d.%d", IP2STR(&pTempIp.ip) );
    lua_pushstring( L, temp );
    sprintf(temp, "%d.%d.%d.%d", IP2STR(&pTempIp.netmask) );
    lua_pushstring( L, temp );
    sprintf(temp, "%d.%d.%d.%d", IP2STR(&pTempIp.gw) );
    lua_pushstring( L, temp );
    return 3;
  }
}