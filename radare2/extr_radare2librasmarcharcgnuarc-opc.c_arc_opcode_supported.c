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
struct arc_opcode {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ARC_HAVE_CPU (int /*<<< orphan*/ ) ; 
 int ARC_OPCODE_CPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_type ; 

int
arc_opcode_supported (const struct arc_opcode *opcode)
{
	if (ARC_OPCODE_CPU (opcode->flags) == 0) {
		return 1;
	}
	if (ARC_OPCODE_CPU (opcode->flags) & ARC_HAVE_CPU (cpu_type)) {
		return 1;
	}
	return 0;
}