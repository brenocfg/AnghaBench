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
struct txdb {int size; int /*<<< orphan*/  start; int /*<<< orphan*/  wptr; int /*<<< orphan*/  rptr; scalar_t__ end; } ;
struct tx_map {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FIFO_SIZE ; 
 int /*<<< orphan*/  vmalloc (int) ; 

__attribute__((used)) static int bdx_tx_db_init(struct txdb *d, int sz_type)
{
	int memsz = FIFO_SIZE * (1 << (sz_type + 1));

	d->start = vmalloc(memsz);
	if (!d->start)
		return -ENOMEM;

	/*
	 * In order to differentiate between db is empty and db is full
	 * states at least one element should always be empty in order to
	 * avoid rptr == wptr which means db is empty
	 */
	d->size = memsz / sizeof(struct tx_map) - 1;
	d->end = d->start + d->size + 1;	/* just after last element */

	/* all dbs are created equally empty */
	d->rptr = d->start;
	d->wptr = d->start;

	return 0;
}