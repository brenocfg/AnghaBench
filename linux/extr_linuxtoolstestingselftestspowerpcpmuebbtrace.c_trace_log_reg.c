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
typedef  int /*<<< orphan*/  value ;
typedef  void* u64 ;
struct trace_entry {scalar_t__ data; int /*<<< orphan*/  type; } ;
struct trace_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  TRACE_TYPE_REG ; 
 struct trace_entry* trace_alloc_entry (struct trace_buffer*,int) ; 

int trace_log_reg(struct trace_buffer *tb, u64 reg, u64 value)
{
	struct trace_entry *e;
	u64 *p;

	e = trace_alloc_entry(tb, sizeof(reg) + sizeof(value));
	if (!e)
		return -ENOSPC;

	e->type = TRACE_TYPE_REG;
	p = (u64 *)e->data;
	*p++ = reg;
	*p++ = value;

	return 0;
}