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
 int /*<<< orphan*/  check_fifo_magic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtc_fifo_drop_samples (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtcfifo_drop (lua_State *L)
{
  check_fifo_magic (L);

  rtc_fifo_drop_samples (luaL_checknumber (L, 1));
  return 0;
}