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
struct auxtrace_heap {scalar_t__ heap_sz; scalar_t__ heap_cnt; int /*<<< orphan*/  heap_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

void auxtrace_heap__free(struct auxtrace_heap *heap)
{
	zfree(&heap->heap_array);
	heap->heap_cnt = 0;
	heap->heap_sz = 0;
}