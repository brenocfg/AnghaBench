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
 int /*<<< orphan*/  callback_free_one (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__** data ; 

__attribute__((used)) static void callback_free(lua_State* L, unsigned int id, int mask)
{
  DATA *d = data[id];

  if (d) {
    int i;
    for (i = 0; i < CALLBACK_COUNT; i++) {
      if (mask & (1 << i)) {
	callback_free_one(L, &d->callback[i]);
      }
    }
  }
}