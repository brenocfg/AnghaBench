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
struct squashfs_stream {int /*<<< orphan*/  stream; } ;
struct squashfs_sb_info {TYPE_1__* decompressor; struct squashfs_stream* stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct squashfs_stream*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void squashfs_decompressor_destroy(struct squashfs_sb_info *msblk)
{
	struct squashfs_stream *stream = msblk->stream;

	if (stream) {
		msblk->decompressor->free(stream->stream);
		kfree(stream);
	}
}