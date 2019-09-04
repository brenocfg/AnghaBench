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
typedef  int /*<<< orphan*/  va_list ;
struct p9_req_t {int /*<<< orphan*/  tc; } ;
struct p9_client {scalar_t__ status; int /*<<< orphan*/  proto_version; int /*<<< orphan*/  tagpool; } ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 scalar_t__ BeginDisconnect ; 
 scalar_t__ Disconnected ; 
 int EIO ; 
 int ENOMEM ; 
 struct p9_req_t* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  P9_DEBUG_MUX ; 
 int P9_NOTAG ; 
 int /*<<< orphan*/  P9_TCLUNK ; 
 int /*<<< orphan*/  P9_TVERSION ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct p9_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_free_req (struct p9_client*,struct p9_req_t*) ; 
 int p9_idpool_get (int /*<<< orphan*/ ) ; 
 struct p9_req_t* p9_tag_alloc (struct p9_client*,int,int) ; 
 int /*<<< orphan*/  p9pdu_finalize (struct p9_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9pdu_prepare (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int p9pdu_vwritef (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_9p_client_req (struct p9_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct p9_req_t *p9_client_prepare_req(struct p9_client *c,
					      int8_t type, int req_size,
					      const char *fmt, va_list ap)
{
	int tag, err;
	struct p9_req_t *req;

	p9_debug(P9_DEBUG_MUX, "client %p op %d\n", c, type);

	/* we allow for any status other than disconnected */
	if (c->status == Disconnected)
		return ERR_PTR(-EIO);

	/* if status is begin_disconnected we allow only clunk request */
	if ((c->status == BeginDisconnect) && (type != P9_TCLUNK))
		return ERR_PTR(-EIO);

	tag = P9_NOTAG;
	if (type != P9_TVERSION) {
		tag = p9_idpool_get(c->tagpool);
		if (tag < 0)
			return ERR_PTR(-ENOMEM);
	}

	req = p9_tag_alloc(c, tag, req_size);
	if (IS_ERR(req))
		return req;

	/* marshall the data */
	p9pdu_prepare(req->tc, tag, type);
	err = p9pdu_vwritef(req->tc, c->proto_version, fmt, ap);
	if (err)
		goto reterr;
	p9pdu_finalize(c, req->tc);
	trace_9p_client_req(c, type, tag);
	return req;
reterr:
	p9_free_req(c, req);
	return ERR_PTR(err);
}