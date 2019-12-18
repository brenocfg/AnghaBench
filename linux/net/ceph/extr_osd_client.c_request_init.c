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
struct ceph_osd_request {int /*<<< orphan*/  r_t; int /*<<< orphan*/  r_private_item; int /*<<< orphan*/  r_mc_node; int /*<<< orphan*/  r_node; int /*<<< orphan*/  r_completion; int /*<<< orphan*/  r_kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ceph_osd_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  target_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void request_init(struct ceph_osd_request *req)
{
	/* req only, each op is zeroed in _osd_req_op_init() */
	memset(req, 0, sizeof(*req));

	kref_init(&req->r_kref);
	init_completion(&req->r_completion);
	RB_CLEAR_NODE(&req->r_node);
	RB_CLEAR_NODE(&req->r_mc_node);
	INIT_LIST_HEAD(&req->r_private_item);

	target_init(&req->r_t);
}