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
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ hexagon_opcode ;

/* Variables and functions */
 scalar_t__ HEXAGON_CODE_CPU (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_type ; 

int
hexagon_opcode_supported
(const hexagon_opcode *opcode)
{
  return (HEXAGON_CODE_CPU (opcode->flags) <= cpu_type);
}