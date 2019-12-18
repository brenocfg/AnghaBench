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
struct z_erofs_collector {scalar_t__ mode; struct z_erofs_collection* cl; int /*<<< orphan*/  vector; } ;
struct z_erofs_collection {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ COLLECT_PRIMARY_FOLLOWED_NOINPLACE ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  z_erofs_collection_put (struct z_erofs_collection*) ; 
 int /*<<< orphan*/  z_erofs_pagevec_ctor_exit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool z_erofs_collector_end(struct z_erofs_collector *clt)
{
	struct z_erofs_collection *cl = clt->cl;

	if (!cl)
		return false;

	z_erofs_pagevec_ctor_exit(&clt->vector, false);
	mutex_unlock(&cl->lock);

	/*
	 * if all pending pages are added, don't hold its reference
	 * any longer if the pcluster isn't hosted by ourselves.
	 */
	if (clt->mode < COLLECT_PRIMARY_FOLLOWED_NOINPLACE)
		z_erofs_collection_put(cl);

	clt->cl = NULL;
	return true;
}