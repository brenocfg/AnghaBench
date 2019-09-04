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

/* Variables and functions */
 scalar_t__ luaR_findentryN (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int luaH_getn_ro (void *t) {
  int i = 1, len=0;

  while(luaR_findentryN(t, i ++, NULL))
    len ++;
  return len;
}