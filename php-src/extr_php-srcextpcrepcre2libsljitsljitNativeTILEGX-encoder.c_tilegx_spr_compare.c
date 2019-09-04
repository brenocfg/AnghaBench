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
struct tilegx_spr {int number; } ;

/* Variables and functions */

__attribute__((used)) static int
tilegx_spr_compare (const void *a_ptr, const void *b_ptr)
{
  const struct tilegx_spr *a = (const struct tilegx_spr *) a_ptr;
  const struct tilegx_spr *b = (const struct tilegx_spr *) b_ptr;
  return (a->number - b->number);
}