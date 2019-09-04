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
struct TYPE_4__ {int length; } ;
typedef  TYPE_1__ tms320_dasm_t ;

/* Variables and functions */
 scalar_t__ field_value (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_cr ; 
 int /*<<< orphan*/  q_lr ; 

__attribute__((used)) static int full_insn_size(tms320_dasm_t * dasm)
{
	int qualifier_size = 0;

	if (field_value (dasm, q_cr)) {
		qualifier_size = 1;
	}
	if (field_value (dasm, q_lr)) {
		qualifier_size = 1;
	}

	return dasm->length + qualifier_size;
}