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
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dht ; 
 double dht_getHumidity () ; 
 double dht_getTemperature () ; 
 int /*<<< orphan*/  dht_read (unsigned int) ; 
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dht_lapi_readxx( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( dht, id );
  lua_pushinteger( L, dht_read(id) );
  double temp = dht_getTemperature();
  double humi = dht_getHumidity();
  int tempdec = (int)((temp - (int)temp) * 1000);
  int humidec = (int)((humi - (int)humi) * 1000);
  lua_pushnumber( L, temp );
  lua_pushnumber( L, humi );
  lua_pushnumber( L, tempdec );
  lua_pushnumber( L, humidec );
  return 5;
}