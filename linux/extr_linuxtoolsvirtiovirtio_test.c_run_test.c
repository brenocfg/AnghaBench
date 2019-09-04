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
struct vq_info {int /*<<< orphan*/  vq; } ;
struct vdev_info {int /*<<< orphan*/  control; scalar_t__ buf; int /*<<< orphan*/  buf_size; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  VHOST_TEST_RUN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long long) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ unlikely (int) ; 
 int virtqueue_add_outbuf (int /*<<< orphan*/ ,struct scatterlist*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_disable_cb (int /*<<< orphan*/ ) ; 
 scalar_t__ virtqueue_enable_cb (int /*<<< orphan*/ ) ; 
 scalar_t__ virtqueue_enable_cb_delayed (int /*<<< orphan*/ ) ; 
 scalar_t__ virtqueue_get_buf (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  virtqueue_kick (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_interrupt (struct vdev_info*) ; 

__attribute__((used)) static void run_test(struct vdev_info *dev, struct vq_info *vq,
		     bool delayed, int bufs)
{
	struct scatterlist sl;
	long started = 0, completed = 0;
	long completed_before;
	int r, test = 1;
	unsigned len;
	long long spurious = 0;
	r = ioctl(dev->control, VHOST_TEST_RUN, &test);
	assert(r >= 0);
	for (;;) {
		virtqueue_disable_cb(vq->vq);
		completed_before = completed;
		do {
			if (started < bufs) {
				sg_init_one(&sl, dev->buf, dev->buf_size);
				r = virtqueue_add_outbuf(vq->vq, &sl, 1,
							 dev->buf + started,
							 GFP_ATOMIC);
				if (likely(r == 0)) {
					++started;
					if (unlikely(!virtqueue_kick(vq->vq)))
						r = -1;
				}
			} else
				r = -1;

			/* Flush out completed bufs if any */
			if (virtqueue_get_buf(vq->vq, &len)) {
				++completed;
				r = 0;
			}

		} while (r == 0);
		if (completed == completed_before)
			++spurious;
		assert(completed <= bufs);
		assert(started <= bufs);
		if (completed == bufs)
			break;
		if (delayed) {
			if (virtqueue_enable_cb_delayed(vq->vq))
				wait_for_interrupt(dev);
		} else {
			if (virtqueue_enable_cb(vq->vq))
				wait_for_interrupt(dev);
		}
	}
	test = 0;
	r = ioctl(dev->control, VHOST_TEST_RUN, &test);
	assert(r >= 0);
	fprintf(stderr, "spurious wakeups: 0x%llx\n", spurious);
}