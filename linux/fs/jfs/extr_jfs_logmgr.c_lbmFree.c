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
struct lbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCACHE_LOCK (unsigned long) ; 
 int /*<<< orphan*/  LCACHE_UNLOCK (unsigned long) ; 
 int /*<<< orphan*/  lbmfree (struct lbuf*) ; 

__attribute__((used)) static void lbmFree(struct lbuf * bp)
{
	unsigned long flags;

	LCACHE_LOCK(flags);

	lbmfree(bp);

	LCACHE_UNLOCK(flags);
}