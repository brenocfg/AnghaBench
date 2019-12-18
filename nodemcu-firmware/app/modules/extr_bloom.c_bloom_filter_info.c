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
typedef  int uint64 ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int size; int fns; int occupancy; } ;
typedef  TYPE_1__ bloom_t ;

/* Variables and functions */
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int bloom_filter_info(lua_State *L) {
  bloom_t *filter = (bloom_t *)luaL_checkudata(L, 1, "bloom.filter");

  lua_pushinteger(L, filter->size << 5);
  lua_pushinteger(L, filter->fns);
  lua_pushinteger(L, filter->occupancy);

  // Now calculate the chance that a FP will be returned
  uint64 prob = 1000000;
  if (filter->occupancy > 0) {
    unsigned int ratio = (filter->size << 5) / filter->occupancy;
    int i;

    prob = ratio;

    for (i = 1; i < filter->fns && prob < 1000000; i++) {
      prob = prob * ratio;
    }

    if (prob < 1000000) {
      // try again with some scaling
      unsigned int ratio256 = (filter->size << 13) / filter->occupancy;

      uint64 prob256 = ratio256;

      for (i = 1; i < filter->fns && prob256 < 256000000; i++) {
        prob256 = (prob256 * ratio256) >> 8;
      }

      prob = prob256 >> 8;
    }
  }

  lua_pushinteger(L, prob > 1000000 ? 1000000 : (int) prob);

  return 4;
}