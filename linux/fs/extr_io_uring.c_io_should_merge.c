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
struct kiocb {int ki_pos; int /*<<< orphan*/ * ki_filp; } ;
struct async_list {int io_start; int io_len; int /*<<< orphan*/ * file; } ;
typedef  int off_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SIZE ; 

__attribute__((used)) static inline bool io_should_merge(struct async_list *al, struct kiocb *kiocb)
{
	if (al->file == kiocb->ki_filp) {
		off_t start, end;

		/*
		 * Allow merging if we're anywhere in the range of the same
		 * page. Generally this happens for sub-page reads or writes,
		 * and it's beneficial to allow the first worker to bring the
		 * page in and the piggy backed work can then work on the
		 * cached page.
		 */
		start = al->io_start & PAGE_MASK;
		end = (al->io_start + al->io_len + PAGE_SIZE - 1) & PAGE_MASK;
		if (kiocb->ki_pos >= start && kiocb->ki_pos <= end)
			return true;
	}

	al->file = NULL;
	return false;
}