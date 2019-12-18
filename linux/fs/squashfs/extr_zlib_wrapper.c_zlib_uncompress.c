#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ avail_out; scalar_t__ avail_in; int total_out; int /*<<< orphan*/ * next_out; scalar_t__ next_in; } ;
typedef  TYPE_1__ z_stream ;
struct squashfs_sb_info {scalar_t__ devblksize; } ;
struct squashfs_page_actor {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int EIO ; 
 void* PAGE_SIZE ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  Z_SYNC_FLUSH ; 
 int min (int,scalar_t__) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  squashfs_finish_page (struct squashfs_page_actor*) ; 
 int /*<<< orphan*/ * squashfs_first_page (struct squashfs_page_actor*) ; 
 int /*<<< orphan*/ * squashfs_next_page (struct squashfs_page_actor*) ; 
 int zlib_inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int zlib_inflateEnd (TYPE_1__*) ; 
 int zlib_inflateInit (TYPE_1__*) ; 

__attribute__((used)) static int zlib_uncompress(struct squashfs_sb_info *msblk, void *strm,
	struct buffer_head **bh, int b, int offset, int length,
	struct squashfs_page_actor *output)
{
	int zlib_err, zlib_init = 0, k = 0;
	z_stream *stream = strm;

	stream->avail_out = PAGE_SIZE;
	stream->next_out = squashfs_first_page(output);
	stream->avail_in = 0;

	do {
		if (stream->avail_in == 0 && k < b) {
			int avail = min(length, msblk->devblksize - offset);
			length -= avail;
			stream->next_in = bh[k]->b_data + offset;
			stream->avail_in = avail;
			offset = 0;
		}

		if (stream->avail_out == 0) {
			stream->next_out = squashfs_next_page(output);
			if (stream->next_out != NULL)
				stream->avail_out = PAGE_SIZE;
		}

		if (!zlib_init) {
			zlib_err = zlib_inflateInit(stream);
			if (zlib_err != Z_OK) {
				squashfs_finish_page(output);
				goto out;
			}
			zlib_init = 1;
		}

		zlib_err = zlib_inflate(stream, Z_SYNC_FLUSH);

		if (stream->avail_in == 0 && k < b)
			put_bh(bh[k++]);
	} while (zlib_err == Z_OK);

	squashfs_finish_page(output);

	if (zlib_err != Z_STREAM_END)
		goto out;

	zlib_err = zlib_inflateEnd(stream);
	if (zlib_err != Z_OK)
		goto out;

	if (k < b)
		goto out;

	return stream->total_out;

out:
	for (; k < b; k++)
		put_bh(bh[k]);

	return -EIO;
}