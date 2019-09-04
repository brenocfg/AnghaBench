#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct p9_req_t {TYPE_1__* rc; TYPE_1__* tc; int /*<<< orphan*/  status; int /*<<< orphan*/  wq; } ;
struct p9_client {int max_tag; struct p9_req_t** reqs; int /*<<< orphan*/  lock; int /*<<< orphan*/  msize; } ;
struct TYPE_3__ {int tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct p9_req_t* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int P9_ROW_MAXTAG ; 
 int /*<<< orphan*/  REQ_STATUS_ALLOC ; 
 int /*<<< orphan*/  REQ_STATUS_IDLE ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct p9_req_t* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int min (int /*<<< orphan*/ ,unsigned int) ; 
 void* p9_fcall_alloc (int) ; 
 int /*<<< orphan*/  p9pdu_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct p9_req_t *
p9_tag_alloc(struct p9_client *c, u16 tag, unsigned int max_size)
{
	unsigned long flags;
	int row, col;
	struct p9_req_t *req;
	int alloc_msize = min(c->msize, max_size);

	/* This looks up the original request by tag so we know which
	 * buffer to read the data into */
	tag++;

	if (tag >= c->max_tag) {
		spin_lock_irqsave(&c->lock, flags);
		/* check again since original check was outside of lock */
		while (tag >= c->max_tag) {
			row = (tag / P9_ROW_MAXTAG);
			c->reqs[row] = kcalloc(P9_ROW_MAXTAG,
					sizeof(struct p9_req_t), GFP_ATOMIC);

			if (!c->reqs[row]) {
				pr_err("Couldn't grow tag array\n");
				spin_unlock_irqrestore(&c->lock, flags);
				return ERR_PTR(-ENOMEM);
			}
			for (col = 0; col < P9_ROW_MAXTAG; col++) {
				req = &c->reqs[row][col];
				req->status = REQ_STATUS_IDLE;
				init_waitqueue_head(&req->wq);
			}
			c->max_tag += P9_ROW_MAXTAG;
		}
		spin_unlock_irqrestore(&c->lock, flags);
	}
	row = tag / P9_ROW_MAXTAG;
	col = tag % P9_ROW_MAXTAG;

	req = &c->reqs[row][col];
	if (!req->tc)
		req->tc = p9_fcall_alloc(alloc_msize);
	if (!req->rc)
		req->rc = p9_fcall_alloc(alloc_msize);
	if (!req->tc || !req->rc)
		goto grow_failed;

	p9pdu_reset(req->tc);
	p9pdu_reset(req->rc);

	req->tc->tag = tag-1;
	req->status = REQ_STATUS_ALLOC;

	return req;

grow_failed:
	pr_err("Couldn't grow tag array\n");
	kfree(req->tc);
	kfree(req->rc);
	req->tc = req->rc = NULL;
	return ERR_PTR(-ENOMEM);
}