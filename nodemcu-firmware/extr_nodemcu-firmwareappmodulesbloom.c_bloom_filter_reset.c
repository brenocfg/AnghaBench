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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int size; scalar_t__ occupancy; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ bloom_t ;

/* Variables and functions */
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bloom_filter_reset(lua_State *L) {
  bloom_t *filter = (bloom_t *)luaL_checkudata(L, 1, "bloom.filter");

  memset(filter->buf, 0, filter->size << 2);
  filter->occupancy = 0;

  return 0;
}