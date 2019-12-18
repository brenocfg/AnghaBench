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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ isr0 ; 
 scalar_t__ isr1 ; 
 scalar_t__ isr10 ; 
 scalar_t__ isr11 ; 
 scalar_t__ isr12 ; 
 scalar_t__ isr13 ; 
 scalar_t__ isr14 ; 
 scalar_t__ isr15 ; 
 scalar_t__ isr16 ; 
 scalar_t__ isr17 ; 
 scalar_t__ isr18 ; 
 scalar_t__ isr19 ; 
 scalar_t__ isr2 ; 
 scalar_t__ isr20 ; 
 scalar_t__ isr21 ; 
 scalar_t__ isr22 ; 
 scalar_t__ isr23 ; 
 scalar_t__ isr24 ; 
 scalar_t__ isr25 ; 
 scalar_t__ isr26 ; 
 scalar_t__ isr27 ; 
 scalar_t__ isr28 ; 
 scalar_t__ isr29 ; 
 scalar_t__ isr3 ; 
 scalar_t__ isr30 ; 
 scalar_t__ isr31 ; 
 scalar_t__ isr4 ; 
 scalar_t__ isr5 ; 
 scalar_t__ isr6 ; 
 scalar_t__ isr7 ; 
 scalar_t__ isr8 ; 
 scalar_t__ isr9 ; 
 int /*<<< orphan*/  set_idt () ; 
 int /*<<< orphan*/  set_idt_gate (int,int /*<<< orphan*/ ) ; 

void isr_install() {
    set_idt_gate(0, (u32)isr0);
    set_idt_gate(1, (u32)isr1);
    set_idt_gate(2, (u32)isr2);
    set_idt_gate(3, (u32)isr3);
    set_idt_gate(4, (u32)isr4);
    set_idt_gate(5, (u32)isr5);
    set_idt_gate(6, (u32)isr6);
    set_idt_gate(7, (u32)isr7);
    set_idt_gate(8, (u32)isr8);
    set_idt_gate(9, (u32)isr9);
    set_idt_gate(10, (u32)isr10);
    set_idt_gate(11, (u32)isr11);
    set_idt_gate(12, (u32)isr12);
    set_idt_gate(13, (u32)isr13);
    set_idt_gate(14, (u32)isr14);
    set_idt_gate(15, (u32)isr15);
    set_idt_gate(16, (u32)isr16);
    set_idt_gate(17, (u32)isr17);
    set_idt_gate(18, (u32)isr18);
    set_idt_gate(19, (u32)isr19);
    set_idt_gate(20, (u32)isr20);
    set_idt_gate(21, (u32)isr21);
    set_idt_gate(22, (u32)isr22);
    set_idt_gate(23, (u32)isr23);
    set_idt_gate(24, (u32)isr24);
    set_idt_gate(25, (u32)isr25);
    set_idt_gate(26, (u32)isr26);
    set_idt_gate(27, (u32)isr27);
    set_idt_gate(28, (u32)isr28);
    set_idt_gate(29, (u32)isr29);
    set_idt_gate(30, (u32)isr30);
    set_idt_gate(31, (u32)isr31);

    set_idt(); // Load with ASM
}