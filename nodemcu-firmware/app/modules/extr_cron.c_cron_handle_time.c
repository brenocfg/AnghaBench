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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct cronent_desc {int mon; int dom; int dow; int hour; int min; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int mon; int dom; int dow; int hour; int min; } ;
struct TYPE_5__ {int /*<<< orphan*/  cb_ref; TYPE_1__ desc; } ;
typedef  TYPE_2__ cronent_ud_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 size_t cronent_count ; 
 int /*<<< orphan*/ * cronent_list ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void cron_handle_time(uint8_t mon, uint8_t dom, uint8_t dow, uint8_t hour, uint8_t min) {
  lua_State *L = lua_getstate();
  struct cronent_desc desc;
  desc.mon  = (uint16_t)1 << (mon - 1);
  desc.dom  = (uint32_t)1 << (dom - 1);
  desc.dow  = ( uint8_t)1 << dow;
  desc.hour = (uint32_t)1 << hour;
  desc.min  = (uint64_t)1 << min;
  for (size_t i = 0; i < cronent_count; i++) {
    lua_rawgeti(L, LUA_REGISTRYINDEX, cronent_list[i]);
    cronent_ud_t *ent = lua_touserdata(L, -1);
    lua_pop(L, 1);
    if ((ent->desc.mon  & desc.mon ) == 0) continue;
    if ((ent->desc.dom  & desc.dom ) == 0) continue;
    if ((ent->desc.dow  & desc.dow ) == 0) continue;
    if ((ent->desc.hour & desc.hour) == 0) continue;
    if ((ent->desc.min  & desc.min ) == 0) continue;
    lua_rawgeti(L, LUA_REGISTRYINDEX, ent->cb_ref);
    lua_rawgeti(L, LUA_REGISTRYINDEX, cronent_list[i]);
    lua_call(L, 1, 0);
  }
}