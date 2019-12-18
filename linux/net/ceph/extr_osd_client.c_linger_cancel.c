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
struct ceph_osd_linger_request {struct ceph_osd_client* osdc; } ;
struct ceph_osd_client {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __linger_cancel (struct ceph_osd_linger_request*) ; 
 scalar_t__ __linger_registered (struct ceph_osd_linger_request*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void linger_cancel(struct ceph_osd_linger_request *lreq)
{
	struct ceph_osd_client *osdc = lreq->osdc;

	down_write(&osdc->lock);
	if (__linger_registered(lreq))
		__linger_cancel(lreq);
	up_write(&osdc->lock);
}