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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/ * callback; } ;
typedef  TYPE_1__ DATA ;

/* Variables and functions */
 int /*<<< orphan*/  callback_callOne (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void callback_call(lua_State* L, DATA *d, int cbnum, int arg, uint32_t time)
{
  if (d) {
    callback_callOne(L, d->callback[cbnum], 1 << cbnum, arg, time);
  }
}