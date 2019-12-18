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
struct trace_iterator {TYPE_1__* ent; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  TRACE_MMIO_MAP 130 
#define  TRACE_MMIO_RW 129 
#define  TRACE_PRINT 128 
 int TRACE_TYPE_HANDLED ; 
 int mmio_print_map (struct trace_iterator*) ; 
 int mmio_print_mark (struct trace_iterator*) ; 
 int mmio_print_rw (struct trace_iterator*) ; 

__attribute__((used)) static enum print_line_t mmio_print_line(struct trace_iterator *iter)
{
	switch (iter->ent->type) {
	case TRACE_MMIO_RW:
		return mmio_print_rw(iter);
	case TRACE_MMIO_MAP:
		return mmio_print_map(iter);
	case TRACE_PRINT:
		return mmio_print_mark(iter);
	default:
		return TRACE_TYPE_HANDLED; /* ignore unknown entries */
	}
}