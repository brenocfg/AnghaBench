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
struct ocfs2_dir_block_trailer {int dummy; } ;

/* Variables and functions */

struct ocfs2_dir_block_trailer *ocfs2_dir_trailer_from_size(int blocksize,
							    void *data)
{
	char *p = data;

	p += blocksize - sizeof(struct ocfs2_dir_block_trailer);
	return (struct ocfs2_dir_block_trailer *)p;
}