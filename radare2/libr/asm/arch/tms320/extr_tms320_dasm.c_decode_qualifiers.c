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
struct TYPE_4__ {int* stream; size_t length; } ;
typedef  TYPE_1__ tms320_dasm_t ;

/* Variables and functions */
 int /*<<< orphan*/  q_cr ; 
 int /*<<< orphan*/  q_lr ; 
 int /*<<< orphan*/  set_field_value (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void decode_qualifiers(tms320_dasm_t * dasm)
{
	switch (dasm->stream[dasm->length]) {
	case 0x98:
		// 1001 1000 - mmap
		break;

	case 0x99:
		// 1001 1001 - port(Smem)
		break;
	case 0x9a:
		// 1001 1010 - port(Smem)
		break;

	case 0x9c:
		// 1001 1100 - <insn>.LR
		set_field_value(dasm, q_lr, 1);
		break;
	case 0x9d:
		// 1001 1101 - <insn>.CR
		set_field_value(dasm, q_cr, 1);
		break;
	}
}