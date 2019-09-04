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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  high_offset; scalar_t__ always0; int /*<<< orphan*/  sel; int /*<<< orphan*/  low_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_CS ; 
 int /*<<< orphan*/  high_16 (int /*<<< orphan*/ ) ; 
 TYPE_1__* idt ; 
 int /*<<< orphan*/  low_16 (int /*<<< orphan*/ ) ; 

void set_idt_gate(int n, u32 handler) {
    idt[n].low_offset = low_16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E; 
    idt[n].high_offset = high_16(handler);
}