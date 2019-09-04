#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ batch; } ;

/* Variables and functions */
 TYPE_1__ array ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ param ; 
 int ptr_ring_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_size ; 

void alloc_ring(void)
{
	int ret = ptr_ring_init(&array, ring_size, 0);
	assert(!ret);
	/* Hacky way to poke at ring internals. Useful for testing though. */
	if (param)
		array.batch = param;
}