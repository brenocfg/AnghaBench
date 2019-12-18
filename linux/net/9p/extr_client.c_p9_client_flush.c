#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct p9_req_t {scalar_t__ status; int /*<<< orphan*/  tc; } ;
struct p9_client {TYPE_1__* trans_mod; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* cancelled ) (struct p9_client*,struct p9_req_t*) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  P9_TFLUSH ; 
 int PTR_ERR (struct p9_req_t*) ; 
 scalar_t__ REQ_STATUS_SENT ; 
 struct p9_req_t* p9_client_rpc (struct p9_client*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int p9_parse_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  p9_tag_remove (struct p9_client*,struct p9_req_t*) ; 
 int /*<<< orphan*/  stub1 (struct p9_client*,struct p9_req_t*) ; 

__attribute__((used)) static int p9_client_flush(struct p9_client *c, struct p9_req_t *oldreq)
{
	struct p9_req_t *req;
	int16_t oldtag;
	int err;

	err = p9_parse_header(&oldreq->tc, NULL, NULL, &oldtag, 1);
	if (err)
		return err;

	p9_debug(P9_DEBUG_9P, ">>> TFLUSH tag %d\n", oldtag);

	req = p9_client_rpc(c, P9_TFLUSH, "w", oldtag);
	if (IS_ERR(req))
		return PTR_ERR(req);

	/*
	 * if we haven't received a response for oldreq,
	 * remove it from the list
	 */
	if (oldreq->status == REQ_STATUS_SENT) {
		if (c->trans_mod->cancelled)
			c->trans_mod->cancelled(c, oldreq);
	}

	p9_tag_remove(c, req);
	return 0;
}