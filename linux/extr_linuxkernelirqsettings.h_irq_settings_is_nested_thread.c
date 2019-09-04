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
struct irq_desc {int status_use_accessors; } ;

/* Variables and functions */
 int _IRQ_NESTED_THREAD ; 

__attribute__((used)) static inline bool irq_settings_is_nested_thread(struct irq_desc *desc)
{
	return desc->status_use_accessors & _IRQ_NESTED_THREAD;
}