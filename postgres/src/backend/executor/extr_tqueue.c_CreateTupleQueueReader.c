#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  shm_mq_handle ;
struct TYPE_4__ {int /*<<< orphan*/ * queue; } ;
typedef  TYPE_1__ TupleQueueReader ;

/* Variables and functions */
 TYPE_1__* palloc0 (int) ; 

TupleQueueReader *
CreateTupleQueueReader(shm_mq_handle *handle)
{
	TupleQueueReader *reader = palloc0(sizeof(TupleQueueReader));

	reader->queue = handle;

	return reader;
}