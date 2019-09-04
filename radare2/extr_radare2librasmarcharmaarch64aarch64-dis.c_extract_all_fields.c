#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum aarch64_field_kind { ____Placeholder_aarch64_field_kind } aarch64_field_kind ;
struct TYPE_4__ {scalar_t__* fields; } ;
typedef  TYPE_1__ aarch64_operand ;
typedef  int /*<<< orphan*/  aarch64_insn ;
struct TYPE_5__ {int /*<<< orphan*/  width; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ FLD_NIL ; 
 int /*<<< orphan*/  extract_field (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* fields ; 

__attribute__((used)) static aarch64_insn
extract_all_fields (const aarch64_operand *self, aarch64_insn code)
{
  aarch64_insn value;
  unsigned int i;
  enum aarch64_field_kind kind;

  value = 0;
  for (i = 0; i < ARRAY_SIZE (self->fields) && self->fields[i] != FLD_NIL; ++i)
    {
      kind = self->fields[i];
      value <<= fields[kind].width;
      value |= extract_field (kind, code, 0);
    }
  return value;
}