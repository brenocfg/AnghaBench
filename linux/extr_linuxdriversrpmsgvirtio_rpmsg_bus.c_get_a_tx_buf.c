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
struct virtproc_info {int last_sbuf; int num_bufs; int buf_size; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  svq; void* sbufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* virtqueue_get_buf (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void *get_a_tx_buf(struct virtproc_info *vrp)
{
	unsigned int len;
	void *ret;

	/* support multiple concurrent senders */
	mutex_lock(&vrp->tx_lock);

	/*
	 * either pick the next unused tx buffer
	 * (half of our buffers are used for sending messages)
	 */
	if (vrp->last_sbuf < vrp->num_bufs / 2)
		ret = vrp->sbufs + vrp->buf_size * vrp->last_sbuf++;
	/* or recycle a used one */
	else
		ret = virtqueue_get_buf(vrp->svq, &len);

	mutex_unlock(&vrp->tx_lock);

	return ret;
}