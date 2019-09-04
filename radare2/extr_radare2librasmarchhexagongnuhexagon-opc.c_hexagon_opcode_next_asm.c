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
struct TYPE_4__ {struct TYPE_4__* next_asm; } ;
typedef  TYPE_1__ hexagon_opcode ;

/* Variables and functions */

const hexagon_opcode *
hexagon_opcode_next_asm
(const hexagon_opcode *op)
{
  if (op)
    op = op->next_asm;

  return (op);
}