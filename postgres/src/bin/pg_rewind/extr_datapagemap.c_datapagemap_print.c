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
typedef  int /*<<< orphan*/  datapagemap_t ;
typedef  int /*<<< orphan*/  datapagemap_iterator_t ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/ * datapagemap_iterate (int /*<<< orphan*/ *) ; 
 scalar_t__ datapagemap_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_log_debug (char*,int /*<<< orphan*/ ) ; 

void
datapagemap_print(datapagemap_t *map)
{
	datapagemap_iterator_t *iter;
	BlockNumber blocknum;

	iter = datapagemap_iterate(map);
	while (datapagemap_next(iter, &blocknum))
		pg_log_debug("block %u", blocknum);

	pg_free(iter);
}