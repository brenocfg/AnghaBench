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
typedef  scalar_t__ u64 ;
struct tracing_map_elt {int dummy; } ;
struct ring_buffer_event {int dummy; } ;
struct hist_field {scalar_t__ (* fn ) (struct hist_field*,struct tracing_map_elt*,struct ring_buffer_event*,void*) ;struct hist_field** operands; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct hist_field*,struct tracing_map_elt*,struct ring_buffer_event*,void*) ; 
 scalar_t__ stub2 (struct hist_field*,struct tracing_map_elt*,struct ring_buffer_event*,void*) ; 

__attribute__((used)) static u64 hist_field_minus(struct hist_field *hist_field,
			    struct tracing_map_elt *elt,
			    struct ring_buffer_event *rbe,
			    void *event)
{
	struct hist_field *operand1 = hist_field->operands[0];
	struct hist_field *operand2 = hist_field->operands[1];

	u64 val1 = operand1->fn(operand1, elt, rbe, event);
	u64 val2 = operand2->fn(operand2, elt, rbe, event);

	return val1 - val2;
}