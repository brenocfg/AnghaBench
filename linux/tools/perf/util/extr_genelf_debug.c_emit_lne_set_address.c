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
struct buffer_ext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_LNE_set_address ; 
 int /*<<< orphan*/  emit_extended_opcode (struct buffer_ext*,int /*<<< orphan*/ ,void**,int) ; 

__attribute__((used)) static void emit_lne_set_address(struct buffer_ext *be,
				 void *address)
{
	emit_extended_opcode(be, DW_LNE_set_address, &address, sizeof(unsigned long));
}