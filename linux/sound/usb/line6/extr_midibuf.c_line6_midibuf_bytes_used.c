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
struct midi_buffer {int pos_write; int pos_read; int size; } ;

/* Variables and functions */
 scalar_t__ midibuf_is_empty (struct midi_buffer*) ; 

int line6_midibuf_bytes_used(struct midi_buffer *this)
{
	return
	    midibuf_is_empty(this) ?
	    0 :
	    (this->pos_write - this->pos_read + this->size - 1) % this->size +
	    1;
}