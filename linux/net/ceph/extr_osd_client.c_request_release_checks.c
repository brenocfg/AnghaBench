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
struct ceph_osd_request {int r_osd; int /*<<< orphan*/  r_private_item; int /*<<< orphan*/  r_mc_node; int /*<<< orphan*/  r_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void request_release_checks(struct ceph_osd_request *req)
{
	WARN_ON(!RB_EMPTY_NODE(&req->r_node));
	WARN_ON(!RB_EMPTY_NODE(&req->r_mc_node));
	WARN_ON(!list_empty(&req->r_private_item));
	WARN_ON(req->r_osd);
}