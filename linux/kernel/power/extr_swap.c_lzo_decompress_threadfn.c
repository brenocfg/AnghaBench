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
struct dec_data {int ret; int /*<<< orphan*/  done; int /*<<< orphan*/  stop; scalar_t__ unc_len; scalar_t__ unc; int /*<<< orphan*/  cmp_len; scalar_t__ cmp; int /*<<< orphan*/  ready; int /*<<< orphan*/ * thr; int /*<<< orphan*/  go; } ;

/* Variables and functions */
 scalar_t__ LZO_HEADER ; 
 scalar_t__ LZO_UNC_SIZE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ clean_pages_on_decompress ; 
 int /*<<< orphan*/  flush_icache_range (unsigned long,scalar_t__) ; 
 scalar_t__ kthread_should_stop () ; 
 int lzo1x_decompress_safe (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lzo_decompress_threadfn(void *data)
{
	struct dec_data *d = data;

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

		d->unc_len = LZO_UNC_SIZE;
		d->ret = lzo1x_decompress_safe(d->cmp + LZO_HEADER, d->cmp_len,
		                               d->unc, &d->unc_len);
		if (clean_pages_on_decompress)
			flush_icache_range((unsigned long)d->unc,
					   (unsigned long)d->unc + d->unc_len);

		atomic_set(&d->stop, 1);
		wake_up(&d->done);
	}
	return 0;
}