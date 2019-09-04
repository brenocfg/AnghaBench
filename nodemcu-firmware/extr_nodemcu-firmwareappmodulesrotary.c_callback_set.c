#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/ * callback; } ;
typedef  TYPE_1__ DATA ;

/* Variables and functions */
 int CALLBACK_COUNT ; 
 int callback_setOne (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__** data ; 

__attribute__((used)) static int callback_set(lua_State* L, int id, int mask, int arg_number)
{
  DATA *d = data[id];
  int result = 0;

  int i;
  for (i = 0; i < CALLBACK_COUNT; i++) {
    if (mask & (1 << i)) {
      result |= callback_setOne(L, &d->callback[i], arg_number);
    }
  }

  return result;
}