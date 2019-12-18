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
typedef  int /*<<< orphan*/  shm_mq_result ;
struct TYPE_3__ {int /*<<< orphan*/  len; void const* data; } ;
typedef  TYPE_1__ shm_mq_iovec ;
typedef  int /*<<< orphan*/  shm_mq_handle ;
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 int /*<<< orphan*/  shm_mq_sendv (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 

shm_mq_result
shm_mq_send(shm_mq_handle *mqh, Size nbytes, const void *data, bool nowait)
{
	shm_mq_iovec iov;

	iov.data = data;
	iov.len = nbytes;

	return shm_mq_sendv(mqh, &iov, 1, nowait);
}