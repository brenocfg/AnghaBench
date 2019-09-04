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
struct mips_cp0sel_name {unsigned int cp0reg; unsigned int sel; } ;

/* Variables and functions */

__attribute__((used)) static const struct mips_cp0sel_name *
lookup_mips_cp0sel_name (const struct mips_cp0sel_name *names,
			 unsigned int len,
			 unsigned int cp0reg,
			 unsigned int sel)
{
  unsigned int i;

  for (i = 0; i < len; i++) {
	  if (names[i].cp0reg == cp0reg && names[i].sel == sel) {
		  return &names[i];
	  }
  }
  return NULL;
}