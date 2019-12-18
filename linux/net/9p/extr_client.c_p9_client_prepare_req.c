#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_4__ {int /*<<< orphan*/  tag; } ;
struct p9_req_t {TYPE_1__ tc; } ;
struct p9_client {scalar_t__ status; int /*<<< orphan*/  proto_version; } ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 scalar_t__ BeginDisconnect ; 
 scalar_t__ Disconnected ; 
 int EIO ; 
 struct p9_req_t* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  P9_DEBUG_MUX ; 
 int /*<<< orphan*/  P9_TCLUNK ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct p9_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_req_put (struct p9_req_t*) ; 
 struct p9_req_t* p9_tag_alloc (struct p9_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p9_tag_remove (struct p9_client*,struct p9_req_t*) ; 
 int /*<<< orphan*/  p9pdu_finalize (struct p9_client*,TYPE_1__*) ; 
 int /*<<< orphan*/  p9pdu_prepare (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int p9pdu_vwritef (TYPE_1__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_9p_client_req (struct p9_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct p9_req_t *p9_client_prepare_req(struct p9_client *c,
					      int8_t type, int req_size,
					      const char *fmt, va_list ap)
{
	int err;
	struct p9_req_t *req;

	p9_debug(P9_DEBUG_MUX, "client %p op %d\n", c, type);

	/* we allow for any status other than disconnected */
	if (c->status == Disconnected)
		return ERR_PTR(-EIO);

	/* if status is begin_disconnected we allow only clunk request */
	if ((c->status == BeginDisconnect) && (type != P9_TCLUNK))
		return ERR_PTR(-EIO);

	req = p9_tag_alloc(c, type, req_size);
	if (IS_ERR(req))
		return req;

	/* marshall the data */
	p9pdu_prepare(&req->tc, req->tc.tag, type);
	err = p9pdu_vwritef(&req->tc, c->proto_version, fmt, ap);
	if (err)
		goto reterr;
	p9pdu_finalize(c, &req->tc);
	trace_9p_client_req(c, type, req->tc.tag);
	return req;
reterr:
	p9_tag_remove(c, req);
	/* We have to put also the 2nd reference as it won't be used */
	p9_req_put(req);
	return ERR_PTR(err);
}