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
struct midi_buffer {int command_prev; scalar_t__ full; scalar_t__ pos_write; scalar_t__ pos_read; } ;

/* Variables and functions */

void line6_midibuf_reset(struct midi_buffer *this)
{
	this->pos_read = this->pos_write = this->full = 0;
	this->command_prev = -1;
}