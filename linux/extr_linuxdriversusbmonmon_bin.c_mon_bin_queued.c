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
struct mon_reader_bin {unsigned int b_cnt; unsigned int b_out; unsigned int b_size; int /*<<< orphan*/  fetch_lock; int /*<<< orphan*/  b_lock; } ;
struct mon_bin_hdr {unsigned int len_cap; } ;

/* Variables and functions */
 struct mon_bin_hdr* MON_OFF2HDR (struct mon_reader_bin*,unsigned int) ; 
 unsigned int PKT_ALIGN ; 
 unsigned int PKT_SIZE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mon_bin_queued(struct mon_reader_bin *rp)
{
	unsigned int cur_out;
	unsigned int bytes, avail;
	unsigned int size;
	unsigned int nevents;
	struct mon_bin_hdr *ep;
	unsigned long flags;

	mutex_lock(&rp->fetch_lock);

	spin_lock_irqsave(&rp->b_lock, flags);
	avail = rp->b_cnt;
	spin_unlock_irqrestore(&rp->b_lock, flags);

	cur_out = rp->b_out;
	nevents = 0;
	bytes = 0;
	while (bytes < avail) {
		ep = MON_OFF2HDR(rp, cur_out);

		nevents++;
		size = ep->len_cap + PKT_SIZE;
		size = (size + PKT_ALIGN-1) & ~(PKT_ALIGN-1);
		if ((cur_out += size) >= rp->b_size)
			cur_out -= rp->b_size;
		bytes += size;
	}

	mutex_unlock(&rp->fetch_lock);
	return nevents;
}