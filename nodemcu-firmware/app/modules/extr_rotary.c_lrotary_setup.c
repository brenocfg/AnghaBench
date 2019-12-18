#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {unsigned int id; int click_delay_us; int longpress_delay_us; int /*<<< orphan*/ * callback; int /*<<< orphan*/  timer; } ;
typedef  TYPE_1__ DATA ;

/* Variables and functions */
 int CALLBACK_COUNT ; 
 int CLICK_DELAY_US ; 
 int LONGPRESS_DELAY_US ; 
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ROTARY_ALL ; 
 int /*<<< orphan*/  SWTIMER_REG_CB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWTIMER_RESUME ; 
 int /*<<< orphan*/  callback_free (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_1__** data ; 
 int /*<<< orphan*/  lrotary_timer_done ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_timer_setfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ platform_gpio_exists (int) ; 
 int /*<<< orphan*/  rotary ; 
 scalar_t__ rotary_close (unsigned int) ; 
 scalar_t__ rotary_setup (unsigned int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasknumber ; 

__attribute__((used)) static int lrotary_setup( lua_State* L )
{
  unsigned int id;

  id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( rotary, id );

  if (rotary_close(id)) {
    return luaL_error( L, "Unable to close switch." );
  }
  callback_free(L, id, ROTARY_ALL);

  if (!data[id]) {
    data[id] = (DATA *) calloc(1, sizeof(DATA));
    if (!data[id]) {
      return -1;
    }
  }

  DATA *d = data[id];
  memset(d, 0, sizeof(*d));

  d->id = id;

  os_timer_setfn(&d->timer, lrotary_timer_done, (void *) d);
  SWTIMER_REG_CB(lrotary_timer_done, SWTIMER_RESUME);
    //lrotary_timer_done checks time elapsed since last event
    //My guess: Since proper functionality relies on some variables to be reset via timer callback and state would be invalid anyway.
      //It is probably best to resume this timer so it can reset it's state variables


  int i;
  for (i = 0; i < CALLBACK_COUNT; i++) {
    d->callback[i] = LUA_NOREF;
  }

  d->click_delay_us = CLICK_DELAY_US;
  d->longpress_delay_us = LONGPRESS_DELAY_US;

  int phase_a = luaL_checkinteger(L, 2);
  luaL_argcheck(L, platform_gpio_exists(phase_a) && phase_a > 0, 2, "Invalid pin");
  int phase_b = luaL_checkinteger(L, 3);
  luaL_argcheck(L, platform_gpio_exists(phase_b) && phase_b > 0, 3, "Invalid pin");
  int press;
  if (lua_gettop(L) >= 4) {
    press = luaL_checkinteger(L, 4);
    luaL_argcheck(L, platform_gpio_exists(press) && press > 0, 4, "Invalid pin");
  } else {
    press = -1;
  }

  if (lua_gettop(L) >= 5) {
    d->longpress_delay_us = 1000 * luaL_checkinteger(L, 5);
    luaL_argcheck(L, d->longpress_delay_us > 0, 5, "Invalid timeout");
  }

  if (lua_gettop(L) >= 6) {
    d->click_delay_us = 1000 * luaL_checkinteger(L, 6);
    luaL_argcheck(L, d->click_delay_us > 0, 6, "Invalid timeout");
  }

  if (rotary_setup(id, phase_a, phase_b, press, tasknumber)) {
    return luaL_error(L, "Unable to setup rotary switch.");
  }
  return 0;
}