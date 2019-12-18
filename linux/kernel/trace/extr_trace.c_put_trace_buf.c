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
struct TYPE_2__ {int /*<<< orphan*/  nesting; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  this_cpu_dec (int /*<<< orphan*/ ) ; 
 TYPE_1__* trace_percpu_buffer ; 

__attribute__((used)) static void put_trace_buf(void)
{
	/* Don't let the decrement of nesting leak before this */
	barrier();
	this_cpu_dec(trace_percpu_buffer->nesting);
}