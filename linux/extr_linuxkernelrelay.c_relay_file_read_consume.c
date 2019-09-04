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
struct rchan_buf {size_t subbufs_produced; size_t subbufs_consumed; size_t offset; size_t bytes_consumed; size_t* padding; int /*<<< orphan*/  cpu; TYPE_1__* chan; } ;
struct TYPE_2__ {size_t subbuf_size; size_t n_subbufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  relay_subbufs_consumed (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void relay_file_read_consume(struct rchan_buf *buf,
				    size_t read_pos,
				    size_t bytes_consumed)
{
	size_t subbuf_size = buf->chan->subbuf_size;
	size_t n_subbufs = buf->chan->n_subbufs;
	size_t read_subbuf;

	if (buf->subbufs_produced == buf->subbufs_consumed &&
	    buf->offset == buf->bytes_consumed)
		return;

	if (buf->bytes_consumed + bytes_consumed > subbuf_size) {
		relay_subbufs_consumed(buf->chan, buf->cpu, 1);
		buf->bytes_consumed = 0;
	}

	buf->bytes_consumed += bytes_consumed;
	if (!read_pos)
		read_subbuf = buf->subbufs_consumed % n_subbufs;
	else
		read_subbuf = read_pos / buf->chan->subbuf_size;
	if (buf->bytes_consumed + buf->padding[read_subbuf] == subbuf_size) {
		if ((read_subbuf == buf->subbufs_produced % n_subbufs) &&
		    (buf->offset == subbuf_size))
			return;
		relay_subbufs_consumed(buf->chan, buf->cpu, 1);
		buf->bytes_consumed = 0;
	}
}