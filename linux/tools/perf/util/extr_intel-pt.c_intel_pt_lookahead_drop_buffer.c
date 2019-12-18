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
struct intel_pt_queue {struct auxtrace_buffer* old_buffer; struct auxtrace_buffer* buffer; } ;
struct auxtrace_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  auxtrace_buffer__drop_data (struct auxtrace_buffer*) ; 

__attribute__((used)) static void intel_pt_lookahead_drop_buffer(struct intel_pt_queue *ptq,
					   struct auxtrace_buffer *buffer)
{
	if (!buffer || buffer == ptq->buffer || buffer == ptq->old_buffer)
		return;

	auxtrace_buffer__drop_data(buffer);
}