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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MAC2STR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MACSTR ; 
 int /*<<< orphan*/  c_sprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wifi_get_macaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wifi_getmac( lua_State* L, uint8_t mode )
{
  char temp[64];
  uint8_t mac[6];
  wifi_get_macaddr(mode, mac);
  c_sprintf(temp, MACSTR, MAC2STR(mac));
  lua_pushstring( L, temp );
  return 1;
}