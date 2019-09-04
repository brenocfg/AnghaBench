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
struct txdb {struct tx_map* start; struct tx_map* end; struct tx_map* wptr; struct tx_map* rptr; } ;
struct tx_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDX_ASSERT (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void __bdx_tx_db_ptr_next(struct txdb *db, struct tx_map **pptr)
{
	BDX_ASSERT(db == NULL || pptr == NULL);	/* sanity */

	BDX_ASSERT(*pptr != db->rptr &&	/* expect either read */
		   *pptr != db->wptr);	/* or write pointer */

	BDX_ASSERT(*pptr < db->start ||	/* pointer has to be */
		   *pptr >= db->end);	/* in range */

	++*pptr;
	if (unlikely(*pptr == db->end))
		*pptr = db->start;
}