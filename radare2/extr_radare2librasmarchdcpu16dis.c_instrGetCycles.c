#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t opcode; int /*<<< orphan*/  b_type; int /*<<< orphan*/  a_type; } ;
struct TYPE_7__ {size_t opcode; int /*<<< orphan*/  a_type; } ;
struct TYPE_6__ {scalar_t__ opcode; } ;
struct TYPE_9__ {TYPE_3__ b; TYPE_2__ n; TYPE_1__ code; } ;
typedef  TYPE_4__ op ;

/* Variables and functions */
 int needWord (int /*<<< orphan*/ ) ; 
 int* opCycle ; 
 int* opCycleB ; 

__attribute__((used)) static int instrGetCycles(const op* o) {
	if (o->code.opcode == 0)
		return opCycleB[o->n.opcode] + needWord(o->n.a_type);
	return opCycle[o->b.opcode] + needWord(o->b.a_type)
		+ needWord(o->b.b_type);
}