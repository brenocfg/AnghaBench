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
struct esas2r_sg_context {scalar_t__ get_phys_addr; int /*<<< orphan*/  cur_offset; } ;
struct esas2r_request {int /*<<< orphan*/  comp_cb; } ;
struct esas2r_ioctl_fs {scalar_t__ status; int /*<<< orphan*/  data; } ;
struct esas2r_adapter {long fs_api_buffer_size; scalar_t__ fs_api_buffer; int /*<<< orphan*/  fs_api_mutex; scalar_t__ fs_api_command_done; int /*<<< orphan*/  fs_api_waiter; } ;
typedef  scalar_t__ PGETPHYSADDR ;

/* Variables and functions */
 scalar_t__ ATTO_STS_OUT_OF_RSRC ; 
 int EBUSY ; 
 int ENOMEM ; 
 struct esas2r_request* esas2r_alloc_request (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_debug (char*) ; 
 int /*<<< orphan*/  esas2r_free_request (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  esas2r_process_fs_ioctl (struct esas2r_adapter*,struct esas2r_ioctl_fs*,struct esas2r_request*,struct esas2r_sg_context*) ; 
 int /*<<< orphan*/  fs_api_complete_req ; 
 scalar_t__ get_physaddr_fs_api ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,scalar_t__) ; 

int esas2r_read_fs(struct esas2r_adapter *a, char *buf, long off, int count)
{
	if (!a->fs_api_buffer)
		return -ENOMEM;

	if (off == 0) {
		struct esas2r_request *rq;
		struct esas2r_sg_context sgc;
		struct esas2r_ioctl_fs *fs =
			(struct esas2r_ioctl_fs *)a->fs_api_buffer;

		/* If another flash request is already in progress, return. */
		if (mutex_lock_interruptible(&a->fs_api_mutex)) {
busy:
			fs->status = ATTO_STS_OUT_OF_RSRC;
			return -EBUSY;
		}

		/*
		 * Presumeably, someone has already written to the
		 * fs_api_buffer, and now they are reading the node the
		 * response, so now we will actually issue the request to the
		 * chip and reply. Allocate a request
		 */

		rq = esas2r_alloc_request(a);
		if (rq == NULL) {
			esas2r_debug("esas2r_read_fs: out of requests");
			mutex_unlock(&a->fs_api_mutex);
			goto busy;
		}

		rq->comp_cb = fs_api_complete_req;

		/* Set up the SGCONTEXT for to build the s/g table */

		sgc.cur_offset = fs->data;
		sgc.get_phys_addr = (PGETPHYSADDR)get_physaddr_fs_api;

		a->fs_api_command_done = 0;

		if (!esas2r_process_fs_ioctl(a, fs, rq, &sgc)) {
			if (fs->status == ATTO_STS_OUT_OF_RSRC)
				count = -EBUSY;

			goto dont_wait;
		}

		/* Now wait around for it to complete. */

		while (!a->fs_api_command_done)
			wait_event_interruptible(a->fs_api_waiter,
						 a->fs_api_command_done);
		;
dont_wait:
		/* Free the request and keep going */
		mutex_unlock(&a->fs_api_mutex);
		esas2r_free_request(a, (struct esas2r_request *)rq);

		/* Pick up possible error code from above */
		if (count < 0)
			return count;
	}

	if (off > a->fs_api_buffer_size)
		return 0;

	if (count + off > a->fs_api_buffer_size)
		count = a->fs_api_buffer_size - off;

	if (count < 0)
		return 0;

	memcpy(buf, a->fs_api_buffer + off, count);

	return count;
}