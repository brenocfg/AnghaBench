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
typedef  int off_t ;
typedef  int /*<<< orphan*/  datapagemap_t ;
typedef  int /*<<< orphan*/  datapagemap_iterator_t ;
typedef  int BlockNumber ;

/* Variables and functions */
 int BLCKSZ ; 
 int /*<<< orphan*/ * datapagemap_iterate (int /*<<< orphan*/ *) ; 
 scalar_t__ datapagemap_next (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pg_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind_copy_file_range (char const*,int,int,int) ; 

__attribute__((used)) static void
execute_pagemap(datapagemap_t *pagemap, const char *path)
{
	datapagemap_iterator_t *iter;
	BlockNumber blkno;
	off_t		offset;

	iter = datapagemap_iterate(pagemap);
	while (datapagemap_next(iter, &blkno))
	{
		offset = blkno * BLCKSZ;
		rewind_copy_file_range(path, offset, offset + BLCKSZ, false);
		/* Ok, this block has now been copied from new data dir to old */
	}
	pg_free(iter);
}