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
typedef  int /*<<< orphan*/  work_func_t ;
struct linger_work {int /*<<< orphan*/  lreq; int /*<<< orphan*/  pending_item; int /*<<< orphan*/  work; } ;
struct ceph_osd_linger_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct linger_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linger_get (struct ceph_osd_linger_request*) ; 

__attribute__((used)) static struct linger_work *lwork_alloc(struct ceph_osd_linger_request *lreq,
				       work_func_t workfn)
{
	struct linger_work *lwork;

	lwork = kzalloc(sizeof(*lwork), GFP_NOIO);
	if (!lwork)
		return NULL;

	INIT_WORK(&lwork->work, workfn);
	INIT_LIST_HEAD(&lwork->pending_item);
	lwork->lreq = linger_get(lreq);

	return lwork;
}