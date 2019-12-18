#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct state {int dummy; } ;
struct directive {int /*<<< orphan*/  d_inst; int /*<<< orphan*/  d_asm; } ;
struct TYPE_2__ {int in_opcode; int in_reg; int in_mode; int in_operand; } ;

/* Variables and functions */
 int i2u16 (int /*<<< orphan*/ *) ; 
 TYPE_1__* in ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void decode_unknown(struct state *s, struct directive *d) {
#if 0
	printf("Opcode 0x%x reg %d mode %d operand 0x%x",
	       in->in_opcode, in->in_reg, in->in_mode, in->in_operand);
#endif
	sprintf (d->d_asm, "DC 0x%4x", i2u16(&d->d_inst));
}