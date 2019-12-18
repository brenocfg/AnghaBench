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
struct TYPE_3__ {int value; scalar_t__ name; } ;
typedef  TYPE_1__ arg ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static int
lookup_name (const arg *table, const char *name)
{
  const arg *p;

  for (p = table; p->name; ++p) {
	  if (strcmp (name, p->name) == 0) {
		  return p->value;
	  }
  }

  return -1;
}