#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t* fields; } ;
typedef  TYPE_1__ aarch64_operand ;
struct TYPE_5__ {int width; } ;

/* Variables and functions */
 size_t FLD_NIL ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* fields ; 

__attribute__((used)) static inline unsigned
get_operand_field_width (const aarch64_operand *operand, unsigned n)
{
  assert (operand->fields[n] != FLD_NIL);
  return fields[operand->fields[n]].width;
}