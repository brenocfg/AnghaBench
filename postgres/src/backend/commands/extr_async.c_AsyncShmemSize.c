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
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  QueueBackendStatus ;

/* Variables and functions */
 int /*<<< orphan*/  AsyncQueueControl ; 
 scalar_t__ MaxBackends ; 
 int /*<<< orphan*/  NUM_ASYNC_BUFFERS ; 
 int /*<<< orphan*/  SimpleLruShmemSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backend ; 
 int /*<<< orphan*/  mul_size (scalar_t__,int) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Size
AsyncShmemSize(void)
{
	Size		size;

	/* This had better match AsyncShmemInit */
	size = mul_size(MaxBackends + 1, sizeof(QueueBackendStatus));
	size = add_size(size, offsetof(AsyncQueueControl, backend));

	size = add_size(size, SimpleLruShmemSize(NUM_ASYNC_BUFFERS, 0));

	return size;
}