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
struct p9_req_t {int /*<<< orphan*/  rc; } ;
struct p9_getlock {int /*<<< orphan*/  client_id; int /*<<< orphan*/  proc_id; int /*<<< orphan*/  length; int /*<<< orphan*/  start; int /*<<< orphan*/  type; } ;
struct p9_fid {int /*<<< orphan*/  fid; struct p9_client* clnt; } ;
struct p9_client {int /*<<< orphan*/  proto_version; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  P9_TGETLOCK ; 
 int PTR_ERR (struct p9_req_t*) ; 
 struct p9_req_t* p9_client_rpc (struct p9_client*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  p9_tag_remove (struct p9_client*,struct p9_req_t*) ; 
 int p9pdu_readf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_9p_protocol_dump (struct p9_client*,int /*<<< orphan*/ *) ; 

int p9_client_getlock_dotl(struct p9_fid *fid, struct p9_getlock *glock)
{
	int err;
	struct p9_client *clnt;
	struct p9_req_t *req;

	err = 0;
	clnt = fid->clnt;
	p9_debug(P9_DEBUG_9P, ">>> TGETLOCK fid %d, type %i start %lld "
		"length %lld proc_id %d client_id %s\n", fid->fid, glock->type,
		glock->start, glock->length, glock->proc_id, glock->client_id);

	req = p9_client_rpc(clnt, P9_TGETLOCK, "dbqqds", fid->fid,  glock->type,
		glock->start, glock->length, glock->proc_id, glock->client_id);

	if (IS_ERR(req))
		return PTR_ERR(req);

	err = p9pdu_readf(&req->rc, clnt->proto_version, "bqqds", &glock->type,
			  &glock->start, &glock->length, &glock->proc_id,
			  &glock->client_id);
	if (err) {
		trace_9p_protocol_dump(clnt, &req->rc);
		goto error;
	}
	p9_debug(P9_DEBUG_9P, "<<< RGETLOCK type %i start %lld length %lld "
		"proc_id %d client_id %s\n", glock->type, glock->start,
		glock->length, glock->proc_id, glock->client_id);
error:
	p9_tag_remove(clnt, req);
	return err;
}