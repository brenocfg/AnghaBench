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
struct percpu_buffer_node {int dummy; } ;
struct percpu_buffer {TYPE_1__* c; } ;
struct TYPE_2__ {intptr_t offset; struct percpu_buffer_node** array; } ;

/* Variables and functions */

struct percpu_buffer_node *__percpu_buffer_pop(struct percpu_buffer *buffer,
					       int cpu)
{
	struct percpu_buffer_node *head;
	intptr_t offset;

	offset = buffer->c[cpu].offset;
	if (offset == 0)
		return NULL;
	head = buffer->c[cpu].array[offset - 1];
	buffer->c[cpu].offset = offset - 1;
	return head;
}