#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ addr; } ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct TYPE_4__ {scalar_t__ addr; } ;
struct ip_info {TYPE_3__ gw; TYPE_2__ netmask; TYPE_1__ ip; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ SOFTAP_IF ; 
 scalar_t__ STATION_IF ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_key (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wifi_get_ip_info (scalar_t__,struct ip_info*) ; 
 int /*<<< orphan*/  wifi_set_ip_info (scalar_t__,struct ip_info*) ; 
 int /*<<< orphan*/  wifi_softap_dhcps_start () ; 
 int /*<<< orphan*/  wifi_softap_dhcps_stop () ; 
 int /*<<< orphan*/  wifi_station_dhcpc_stop () ; 

__attribute__((used)) static int wifi_setip( lua_State* L, uint8_t mode )
{
  struct ip_info pTempIp;
  wifi_get_ip_info(mode, &pTempIp);

  if (!lua_istable(L, 1))
    return luaL_error( L, "wrong arg type" );
  uint32_t ip = parse_key(L, "ip");
  if(ip!=0)
    pTempIp.ip.addr = ip;

  ip = parse_key(L, "netmask");
  if(ip!=0)
    pTempIp.netmask.addr = ip;

  ip = parse_key(L, "gateway");
  if(mode==SOFTAP_IF || ip!=0)
    pTempIp.gw.addr = ip;

  if(STATION_IF == mode)
  {
    wifi_station_dhcpc_stop();
    lua_pushboolean(L,wifi_set_ip_info(mode, &pTempIp));
  }
  else
  {
    wifi_softap_dhcps_stop();
    lua_pushboolean(L,wifi_set_ip_info(mode, &pTempIp));
    wifi_softap_dhcps_start();
  }

  return 1;
}