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
struct TYPE_2__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ xtensa_lookup_entry ;

/* Variables and functions */
 int r_str_casecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xtensa_isa_name_compare (const void *v1, const void *v2)
{
  xtensa_lookup_entry *e1 = (xtensa_lookup_entry *) v1;
  xtensa_lookup_entry *e2 = (xtensa_lookup_entry *) v2;

  return r_str_casecmp (e1->key, e2->key);
}