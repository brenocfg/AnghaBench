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
struct crc_data {unsigned int run_threads; int /*<<< orphan*/  done; int /*<<< orphan*/  stop; int /*<<< orphan*/ ** unc_len; int /*<<< orphan*/ * unc; int /*<<< orphan*/ * crc32; int /*<<< orphan*/  ready; int /*<<< orphan*/ * thr; int /*<<< orphan*/  go; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crc32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int crc32_threadfn(void *data)
{
	struct crc_data *d = data;
	unsigned i;

	while (1) {
		wait_event(d->go, atomic_read(&d->ready) ||
		                  kthread_should_stop());
		if (kthread_should_stop()) {
			d->thr = NULL;
			atomic_set(&d->stop, 1);
			wake_up(&d->done);
			break;
		}
		atomic_set(&d->ready, 0);

		for (i = 0; i < d->run_threads; i++)
			*d->crc32 = crc32_le(*d->crc32,
			                     d->unc[i], *d->unc_len[i]);
		atomic_set(&d->stop, 1);
		wake_up(&d->done);
	}
	return 0;
}