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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  idt_gate_t ;
struct TYPE_2__ {int limit; scalar_t__ base; } ;

/* Variables and functions */
 int IDT_ENTRIES ; 
 int /*<<< orphan*/  idt ; 
 TYPE_1__ idt_reg ; 

void set_idt() {
    idt_reg.base = (uint32_t) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    asm volatile("lidtl (%0)" : : "r" (&idt_reg));
}