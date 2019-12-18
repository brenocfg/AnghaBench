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
typedef  scalar_t__ shm_mq_result ;
typedef  int /*<<< orphan*/  shm_mq_handle ;
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ SHM_MQ_SUCCESS ; 
 scalar_t__ shm_mq_receive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,int) ; 
 scalar_t__ shm_mq_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void
copy_messages(shm_mq_handle *inqh, shm_mq_handle *outqh)
{
	Size		len;
	void	   *data;
	shm_mq_result res;

	for (;;)
	{
		/* Notice any interrupts that have occurred. */
		CHECK_FOR_INTERRUPTS();

		/* Receive a message. */
		res = shm_mq_receive(inqh, &len, &data, false);
		if (res != SHM_MQ_SUCCESS)
			break;

		/* Send it back out. */
		res = shm_mq_send(outqh, len, data, false);
		if (res != SHM_MQ_SUCCESS)
			break;
	}
}