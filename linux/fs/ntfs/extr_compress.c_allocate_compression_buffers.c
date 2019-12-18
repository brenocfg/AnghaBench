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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NTFS_MAX_CB_SIZE ; 
 int /*<<< orphan*/  ntfs_compression_buffer ; 
 int /*<<< orphan*/  vmalloc (int /*<<< orphan*/ ) ; 

int allocate_compression_buffers(void)
{
	BUG_ON(ntfs_compression_buffer);

	ntfs_compression_buffer = vmalloc(NTFS_MAX_CB_SIZE);
	if (!ntfs_compression_buffer)
		return -ENOMEM;
	return 0;
}