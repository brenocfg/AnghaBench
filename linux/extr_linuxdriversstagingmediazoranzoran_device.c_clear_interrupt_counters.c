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
struct zoran {int JPEG_min_missed; scalar_t__ JPEG_max_missed; scalar_t__ JPEG_missed; scalar_t__ END_event_missed; scalar_t__ JPEG_1; scalar_t__ JPEG_0; scalar_t__ JPEG_out; scalar_t__ JPEG_in; scalar_t__ IRQ1_out; scalar_t__ IRQ1_in; scalar_t__ field_counter; scalar_t__ intr_counter_JPEGRepIRQ; scalar_t__ intr_counter_CodRepIRQ; scalar_t__ intr_counter_GIRQ0; scalar_t__ intr_counter_GIRQ1; } ;

/* Variables and functions */

void
clear_interrupt_counters (struct zoran *zr)
{
	zr->intr_counter_GIRQ1 = 0;
	zr->intr_counter_GIRQ0 = 0;
	zr->intr_counter_CodRepIRQ = 0;
	zr->intr_counter_JPEGRepIRQ = 0;
	zr->field_counter = 0;
	zr->IRQ1_in = 0;
	zr->IRQ1_out = 0;
	zr->JPEG_in = 0;
	zr->JPEG_out = 0;
	zr->JPEG_0 = 0;
	zr->JPEG_1 = 0;
	zr->END_event_missed = 0;
	zr->JPEG_missed = 0;
	zr->JPEG_max_missed = 0;
	zr->JPEG_min_missed = 0x7fffffff;
}