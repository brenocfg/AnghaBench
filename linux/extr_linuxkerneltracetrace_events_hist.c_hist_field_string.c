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
typedef  int /*<<< orphan*/  u64 ;
struct tracing_map_elt {int dummy; } ;
struct ring_buffer_event {int dummy; } ;
struct hist_field {TYPE_1__* field; } ;
struct TYPE_2__ {int offset; } ;

/* Variables and functions */

__attribute__((used)) static u64 hist_field_string(struct hist_field *hist_field,
			     struct tracing_map_elt *elt,
			     struct ring_buffer_event *rbe,
			     void *event)
{
	char *addr = (char *)(event + hist_field->field->offset);

	return (u64)(unsigned long)addr;
}