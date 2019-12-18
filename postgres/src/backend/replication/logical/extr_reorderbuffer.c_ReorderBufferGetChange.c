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
struct TYPE_3__ {int /*<<< orphan*/  change_context; } ;
typedef  int /*<<< orphan*/  ReorderBufferChange ;
typedef  TYPE_1__ ReorderBuffer ;

/* Variables and functions */
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

ReorderBufferChange *
ReorderBufferGetChange(ReorderBuffer *rb)
{
	ReorderBufferChange *change;

	change = (ReorderBufferChange *)
		MemoryContextAlloc(rb->change_context, sizeof(ReorderBufferChange));

	memset(change, 0, sizeof(ReorderBufferChange));
	return change;
}