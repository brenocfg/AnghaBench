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
typedef  int /*<<< orphan*/  hexagon_opcode ;
typedef  int /*<<< orphan*/  hexagon_insn ;

/* Variables and functions */
 size_t HEXAGON_HASH_ICODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const** icode_map ; 

const hexagon_opcode *
hexagon_opcode_lookup_dis
(hexagon_insn insn)
{
if (icode_map) {
  return (icode_map [HEXAGON_HASH_ICODE (insn)]);
}
return NULL;
}