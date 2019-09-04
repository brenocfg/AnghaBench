#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum aarch64_field_kind { ____Placeholder_aarch64_field_kind } aarch64_field_kind ;
struct TYPE_4__ {int width; scalar_t__ lsb; } ;
typedef  TYPE_1__ aarch64_field ;

/* Variables and functions */
 TYPE_1__* fields ; 

__attribute__((used)) static inline int
gen_sub_field (enum aarch64_field_kind kind, int lsb_rel, int width, aarch64_field *ret)
{
  const aarch64_field *field = &fields[kind];
  if (lsb_rel < 0 || width <= 0 || lsb_rel + width > field->width)
    return 0;
  ret->lsb = field->lsb + lsb_rel;
  ret->width = width;
  return 1;
}