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
struct ring_buffer {int /*<<< orphan*/  record_disabled; } ;

/* Variables and functions */
 int RB_BUFFER_OFF ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

bool ring_buffer_record_is_set_on(struct ring_buffer *buffer)
{
	return !(atomic_read(&buffer->record_disabled) & RB_BUFFER_OFF);
}