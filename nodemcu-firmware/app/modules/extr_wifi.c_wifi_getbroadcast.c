#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32 ;
struct TYPE_3__ {int addr; } ;
struct TYPE_4__ {int addr; } ;
struct ip_info {TYPE_1__ netmask; TYPE_2__ ip; } ;
struct ip_addr {int addr; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int IP2STR (struct ip_addr*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  wifi_get_ip_info (int /*<<< orphan*/ ,struct ip_info*) ; 

__attribute__((used)) static int wifi_getbroadcast( lua_State* L, uint8_t mode )
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
    struct ip_addr broadcast_address;

    uint32 subnet_mask32 = pTempIp.netmask.addr & pTempIp.ip.addr;
    uint32 broadcast_address32 = ~pTempIp.netmask.addr | subnet_mask32;
    broadcast_address.addr = broadcast_address32;

    sprintf(temp, "%d.%d.%d.%d", IP2STR(&broadcast_address) );
    lua_pushstring( L, temp );

    return 1;
  }
}