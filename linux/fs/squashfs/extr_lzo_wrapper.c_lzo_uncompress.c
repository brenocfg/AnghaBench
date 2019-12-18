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
struct squashfs_page_actor {size_t length; } ;
struct squashfs_lzo {void* output; void* input; } ;
struct buffer_head {void* b_data; } ;

/* Variables and functions */
 int EIO ; 
 int LZO_E_OK ; 
 int PAGE_SIZE ; 
 int lzo1x_decompress_safe (void*,size_t,void*,size_t*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int min (int,scalar_t__) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  squashfs_finish_page (struct squashfs_page_actor*) ; 
 void* squashfs_first_page (struct squashfs_page_actor*) ; 
 void* squashfs_next_page (struct squashfs_page_actor*) ; 

__attribute__((used)) static int lzo_uncompress(struct squashfs_sb_info *msblk, void *strm,
	struct buffer_head **bh, int b, int offset, int length,
	struct squashfs_page_actor *output)
{
	struct squashfs_lzo *stream = strm;
	void *buff = stream->input, *data;
	int avail, i, bytes = length, res;
	size_t out_len = output->length;

	for (i = 0; i < b; i++) {
		avail = min(bytes, msblk->devblksize - offset);
		memcpy(buff, bh[i]->b_data + offset, avail);
		buff += avail;
		bytes -= avail;
		offset = 0;
		put_bh(bh[i]);
	}

	res = lzo1x_decompress_safe(stream->input, (size_t)length,
					stream->output, &out_len);
	if (res != LZO_E_OK)
		goto failed;

	res = bytes = (int)out_len;
	data = squashfs_first_page(output);
	buff = stream->output;
	while (data) {
		if (bytes <= PAGE_SIZE) {
			memcpy(data, buff, bytes);
			break;
		} else {
			memcpy(data, buff, PAGE_SIZE);
			buff += PAGE_SIZE;
			bytes -= PAGE_SIZE;
			data = squashfs_next_page(output);
		}
	}
	squashfs_finish_page(output);

	return res;

failed:
	return -EIO;
}