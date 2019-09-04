#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int /*<<< orphan*/  device; int /*<<< orphan*/  (* munge ) (int /*<<< orphan*/ ,struct comedi_subdevice*,unsigned int,int,int) ;struct comedi_async* async; } ;
struct TYPE_2__ {int flags; int chanlist_len; } ;
struct comedi_async {unsigned int munge_count; unsigned int prealloc_bufsz; unsigned int munge_ptr; unsigned int prealloc_buf; int munge_chan; TYPE_1__ cmd; } ;

/* Variables and functions */
 int CMDF_RAWDATA ; 
 unsigned int comedi_bytes_per_sample (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct comedi_subdevice*,unsigned int,int,int) ; 

__attribute__((used)) static unsigned int comedi_buf_munge(struct comedi_subdevice *s,
				     unsigned int num_bytes)
{
	struct comedi_async *async = s->async;
	unsigned int count = 0;
	const unsigned int num_sample_bytes = comedi_bytes_per_sample(s);

	if (!s->munge || (async->cmd.flags & CMDF_RAWDATA)) {
		async->munge_count += num_bytes;
		count = num_bytes;
	} else {
		/* don't munge partial samples */
		num_bytes -= num_bytes % num_sample_bytes;
		while (count < num_bytes) {
			int block_size = num_bytes - count;
			unsigned int buf_end;

			buf_end = async->prealloc_bufsz - async->munge_ptr;
			if (block_size > buf_end)
				block_size = buf_end;

			s->munge(s->device, s,
				 async->prealloc_buf + async->munge_ptr,
				 block_size, async->munge_chan);

			/*
			 * ensure data is munged in buffer before the
			 * async buffer munge_count is incremented
			 */
			smp_wmb();

			async->munge_chan += block_size / num_sample_bytes;
			async->munge_chan %= async->cmd.chanlist_len;
			async->munge_count += block_size;
			async->munge_ptr += block_size;
			async->munge_ptr %= async->prealloc_bufsz;
			count += block_size;
		}
	}

	return count;
}