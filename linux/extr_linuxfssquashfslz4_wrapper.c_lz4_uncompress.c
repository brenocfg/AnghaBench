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
struct squashfs_sb_info {scalar_t__ devblksize; } ;
struct squashfs_page_actor {int /*<<< orphan*/  length; } ;
struct squashfs_lz4 {void* output; void* input; } ;
struct buffer_head {void* b_data; } ;

/* Variables and functions */
 int EIO ; 
 int LZ4_decompress_safe (void*,void*,int,int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int min (int,scalar_t__) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  squashfs_finish_page (struct squashfs_page_actor*) ; 
 void* squashfs_first_page (struct squashfs_page_actor*) ; 
 void* squashfs_next_page (struct squashfs_page_actor*) ; 

__attribute__((used)) static int lz4_uncompress(struct squashfs_sb_info *msblk, void *strm,
	struct buffer_head **bh, int b, int offset, int length,
	struct squashfs_page_actor *output)
{
	struct squashfs_lz4 *stream = strm;
	void *buff = stream->input, *data;
	int avail, i, bytes = length, res;

	for (i = 0; i < b; i++) {
		avail = min(bytes, msblk->devblksize - offset);
		memcpy(buff, bh[i]->b_data + offset, avail);
		buff += avail;
		bytes -= avail;
		offset = 0;
		put_bh(bh[i]);
	}

	res = LZ4_decompress_safe(stream->input, stream->output,
		length, output->length);

	if (res < 0)
		return -EIO;

	bytes = res;
	data = squashfs_first_page(output);
	buff = stream->output;
	while (data) {
		if (bytes <= PAGE_SIZE) {
			memcpy(data, buff, bytes);
			break;
		}
		memcpy(data, buff, PAGE_SIZE);
		buff += PAGE_SIZE;
		bytes -= PAGE_SIZE;
		data = squashfs_next_page(output);
	}
	squashfs_finish_page(output);

	return res;
}