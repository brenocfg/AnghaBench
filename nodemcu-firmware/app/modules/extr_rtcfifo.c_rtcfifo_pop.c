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
typedef  int /*<<< orphan*/  sample_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  check_fifo_magic (int /*<<< orphan*/ *) ; 
 int extract_sample (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_fifo_pop_sample (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtcfifo_pop (lua_State *L)
{
  check_fifo_magic (L);

  sample_t s;
  if (!rtc_fifo_pop_sample (&s))
    return 0;
  else
    return extract_sample (L, &s);
}