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
struct squashfs_stream {int dummy; } ;
struct squashfs_sb_info {TYPE_1__* decompressor; struct squashfs_stream* stream; } ;
struct squashfs_page_actor {int dummy; } ;
struct decomp_stream {int /*<<< orphan*/  stream; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int (* decompress ) (struct squashfs_sb_info*,int /*<<< orphan*/ ,struct buffer_head**,int,int,int,struct squashfs_page_actor*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*,int /*<<< orphan*/ ) ; 
 struct decomp_stream* get_decomp_stream (struct squashfs_sb_info*,struct squashfs_stream*) ; 
 int /*<<< orphan*/  put_decomp_stream (struct decomp_stream*,struct squashfs_stream*) ; 
 int stub1 (struct squashfs_sb_info*,int /*<<< orphan*/ ,struct buffer_head**,int,int,int,struct squashfs_page_actor*) ; 

int squashfs_decompress(struct squashfs_sb_info *msblk, struct buffer_head **bh,
	int b, int offset, int length, struct squashfs_page_actor *output)
{
	int res;
	struct squashfs_stream *stream = msblk->stream;
	struct decomp_stream *decomp_stream = get_decomp_stream(msblk, stream);
	res = msblk->decompressor->decompress(msblk, decomp_stream->stream,
		bh, b, offset, length, output);
	put_decomp_stream(decomp_stream, stream);
	if (res < 0)
		ERROR("%s decompression failed, data probably corrupt\n",
			msblk->decompressor->name);
	return res;
}