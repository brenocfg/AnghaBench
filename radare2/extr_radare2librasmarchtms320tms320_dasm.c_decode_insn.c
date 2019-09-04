#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  syntax; TYPE_2__* insn; TYPE_1__* head; int /*<<< orphan*/  length; } ;
typedef  TYPE_3__ tms320_dasm_t ;
typedef  int /*<<< orphan*/  insn_item_t ;
struct TYPE_19__ {int /*<<< orphan*/  syntax; } ;
struct TYPE_18__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  E ; 
 int /*<<< orphan*/  decode_addresses (TYPE_3__*) ; 
 int /*<<< orphan*/  decode_addressing_modes (TYPE_3__*) ; 
 int /*<<< orphan*/  decode_bits (TYPE_3__*) ; 
 int /*<<< orphan*/  decode_braces (TYPE_3__*) ; 
 int /*<<< orphan*/  decode_cond (TYPE_3__*) ; 
 int /*<<< orphan*/  decode_constants (TYPE_3__*) ; 
 int /*<<< orphan*/  decode_qualifiers (TYPE_3__*) ; 
 int /*<<< orphan*/  decode_registers (TYPE_3__*) ; 
 int /*<<< orphan*/  decode_relop (TYPE_3__*) ; 
 int /*<<< orphan*/  decode_swap (TYPE_3__*) ; 
 scalar_t__ field_valid (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ field_value (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * finalize (TYPE_3__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

insn_item_t * decode_insn(tms320_dasm_t * dasm)
{
	dasm->length = dasm->head->size;

	snprintf(dasm->syntax, sizeof(dasm->syntax), \
		 field_valid(dasm, E) && field_value(dasm, E) ? "|| %s" : "%s", dasm->insn->syntax);

	decode_bits(dasm);
	decode_braces(dasm);
	decode_qualifiers(dasm);

	decode_constants(dasm);
	decode_addresses(dasm);

	decode_swap(dasm);
	decode_relop(dasm);
	decode_cond(dasm);

	decode_registers(dasm);
	decode_addressing_modes(dasm);

	return finalize(dasm);

}