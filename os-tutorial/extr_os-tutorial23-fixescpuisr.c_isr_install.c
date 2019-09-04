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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ irq0 ; 
 scalar_t__ irq1 ; 
 scalar_t__ irq10 ; 
 scalar_t__ irq11 ; 
 scalar_t__ irq12 ; 
 scalar_t__ irq13 ; 
 scalar_t__ irq14 ; 
 scalar_t__ irq15 ; 
 scalar_t__ irq2 ; 
 scalar_t__ irq3 ; 
 scalar_t__ irq4 ; 
 scalar_t__ irq5 ; 
 scalar_t__ irq6 ; 
 scalar_t__ irq7 ; 
 scalar_t__ irq8 ; 
 scalar_t__ irq9 ; 
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
 int /*<<< orphan*/  port_byte_out (int,int) ; 
 int /*<<< orphan*/  set_idt () ; 
 int /*<<< orphan*/  set_idt_gate (int,int /*<<< orphan*/ ) ; 

void isr_install() {
    set_idt_gate(0, (uint32_t)isr0);
    set_idt_gate(1, (uint32_t)isr1);
    set_idt_gate(2, (uint32_t)isr2);
    set_idt_gate(3, (uint32_t)isr3);
    set_idt_gate(4, (uint32_t)isr4);
    set_idt_gate(5, (uint32_t)isr5);
    set_idt_gate(6, (uint32_t)isr6);
    set_idt_gate(7, (uint32_t)isr7);
    set_idt_gate(8, (uint32_t)isr8);
    set_idt_gate(9, (uint32_t)isr9);
    set_idt_gate(10, (uint32_t)isr10);
    set_idt_gate(11, (uint32_t)isr11);
    set_idt_gate(12, (uint32_t)isr12);
    set_idt_gate(13, (uint32_t)isr13);
    set_idt_gate(14, (uint32_t)isr14);
    set_idt_gate(15, (uint32_t)isr15);
    set_idt_gate(16, (uint32_t)isr16);
    set_idt_gate(17, (uint32_t)isr17);
    set_idt_gate(18, (uint32_t)isr18);
    set_idt_gate(19, (uint32_t)isr19);
    set_idt_gate(20, (uint32_t)isr20);
    set_idt_gate(21, (uint32_t)isr21);
    set_idt_gate(22, (uint32_t)isr22);
    set_idt_gate(23, (uint32_t)isr23);
    set_idt_gate(24, (uint32_t)isr24);
    set_idt_gate(25, (uint32_t)isr25);
    set_idt_gate(26, (uint32_t)isr26);
    set_idt_gate(27, (uint32_t)isr27);
    set_idt_gate(28, (uint32_t)isr28);
    set_idt_gate(29, (uint32_t)isr29);
    set_idt_gate(30, (uint32_t)isr30);
    set_idt_gate(31, (uint32_t)isr31);

    // Remap the PIC
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0); 

    // Install the IRQs
    set_idt_gate(32, (uint32_t)irq0);
    set_idt_gate(33, (uint32_t)irq1);
    set_idt_gate(34, (uint32_t)irq2);
    set_idt_gate(35, (uint32_t)irq3);
    set_idt_gate(36, (uint32_t)irq4);
    set_idt_gate(37, (uint32_t)irq5);
    set_idt_gate(38, (uint32_t)irq6);
    set_idt_gate(39, (uint32_t)irq7);
    set_idt_gate(40, (uint32_t)irq8);
    set_idt_gate(41, (uint32_t)irq9);
    set_idt_gate(42, (uint32_t)irq10);
    set_idt_gate(43, (uint32_t)irq11);
    set_idt_gate(44, (uint32_t)irq12);
    set_idt_gate(45, (uint32_t)irq13);
    set_idt_gate(46, (uint32_t)irq14);
    set_idt_gate(47, (uint32_t)irq15);

    set_idt(); // Load with ASM
}