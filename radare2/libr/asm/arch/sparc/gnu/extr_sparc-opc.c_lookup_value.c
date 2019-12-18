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
struct TYPE_3__ {char const* name; int value; } ;
typedef  TYPE_1__ arg ;

/* Variables and functions */

__attribute__((used)) static const char *
lookup_value (const arg *table, int value)
{
  const arg *p;

  for (p = table; p->name; ++p) {
	  if (value == p->value) {
		  return p->name;
	  }
  }

  return NULL;
}