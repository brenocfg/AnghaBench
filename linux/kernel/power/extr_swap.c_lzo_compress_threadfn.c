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
struct cmp_data {int ret; int /*<<< orphan*/  done; int /*<<< orphan*/  stop; int /*<<< orphan*/  wrk; int /*<<< orphan*/  cmp_len; scalar_t__ cmp; int /*<<< orphan*/  unc_len; int /*<<< orphan*/  unc; int /*<<< orphan*/  ready; int /*<<< orphan*/ * thr; int /*<<< orphan*/  go; } ;

/* Variables and functions */
 scalar_t__ LZO_HEADER ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ kthread_should_stop () ; 
 int lzo1x_1_compress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lzo_compress_threadfn(void *data)
{
	struct cmp_data *d = data;

	while (1) {
		wait_event(d->go, atomic_read(&d->ready) ||
		                  kthread_should_stop());
		if (kthread_should_stop()) {
			d->thr = NULL;
			d->ret = -1;
			atomic_set(&d->stop, 1);
			wake_up(&d->done);
			break;
		}
		atomic_set(&d->ready, 0);

		d->ret = lzo1x_1_compress(d->unc, d->unc_len,
		                          d->cmp + LZO_HEADER, &d->cmp_len,
		                          d->wrk);
		atomic_set(&d->stop, 1);
		wake_up(&d->done);
	}
	return 0;
}