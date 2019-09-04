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
struct ceph_mon_generic_request {scalar_t__ tid; struct ceph_mon_client* monc; } ;
struct ceph_mon_client {int /*<<< orphan*/  generic_request_tree; scalar_t__ last_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  get_generic_request (struct ceph_mon_generic_request*) ; 
 int /*<<< orphan*/  insert_generic_request (int /*<<< orphan*/ *,struct ceph_mon_generic_request*) ; 

__attribute__((used)) static void register_generic_request(struct ceph_mon_generic_request *req)
{
	struct ceph_mon_client *monc = req->monc;

	WARN_ON(req->tid);

	get_generic_request(req);
	req->tid = ++monc->last_tid;
	insert_generic_request(&monc->generic_request_tree, req);
}