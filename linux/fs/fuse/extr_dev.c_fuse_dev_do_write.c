#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fuse_out_header {size_t len; int unique; int error; } ;
struct TYPE_3__ {struct fuse_out_header h; } ;
struct fuse_req {int /*<<< orphan*/  list; int /*<<< orphan*/  flags; TYPE_1__ out; TYPE_2__* args; } ;
struct fuse_pqueue {int /*<<< orphan*/  lock; scalar_t__ connected; int /*<<< orphan*/  io; } ;
struct fuse_dev {struct fuse_pqueue pq; struct fuse_conn* fc; } ;
struct fuse_copy_state {scalar_t__ move_pages; struct fuse_req* req; } ;
struct fuse_conn {int no_interrupt; int /*<<< orphan*/  iq; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  oh ;
struct TYPE_4__ {int /*<<< orphan*/  page_replace; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int ENOSYS ; 
 int /*<<< orphan*/  FR_LOCKED ; 
 int /*<<< orphan*/  FR_PRIVATE ; 
 int /*<<< orphan*/  FR_SENT ; 
 int FUSE_INT_REQ_BIT ; 
 int /*<<< orphan*/  __fuse_get_request (struct fuse_req*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int copy_out_args (struct fuse_copy_state*,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  fuse_copy_finish (struct fuse_copy_state*) ; 
 int fuse_copy_one (struct fuse_copy_state*,struct fuse_out_header*,int) ; 
 int fuse_notify (struct fuse_conn*,int,size_t,struct fuse_copy_state*) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_request_end (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int queue_interrupt (int /*<<< orphan*/ *,struct fuse_req*) ; 
 struct fuse_req* request_find (struct fuse_pqueue*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t fuse_dev_do_write(struct fuse_dev *fud,
				 struct fuse_copy_state *cs, size_t nbytes)
{
	int err;
	struct fuse_conn *fc = fud->fc;
	struct fuse_pqueue *fpq = &fud->pq;
	struct fuse_req *req;
	struct fuse_out_header oh;

	err = -EINVAL;
	if (nbytes < sizeof(struct fuse_out_header))
		goto out;

	err = fuse_copy_one(cs, &oh, sizeof(oh));
	if (err)
		goto copy_finish;

	err = -EINVAL;
	if (oh.len != nbytes)
		goto copy_finish;

	/*
	 * Zero oh.unique indicates unsolicited notification message
	 * and error contains notification code.
	 */
	if (!oh.unique) {
		err = fuse_notify(fc, oh.error, nbytes - sizeof(oh), cs);
		goto out;
	}

	err = -EINVAL;
	if (oh.error <= -1000 || oh.error > 0)
		goto copy_finish;

	spin_lock(&fpq->lock);
	req = NULL;
	if (fpq->connected)
		req = request_find(fpq, oh.unique & ~FUSE_INT_REQ_BIT);

	err = -ENOENT;
	if (!req) {
		spin_unlock(&fpq->lock);
		goto copy_finish;
	}

	/* Is it an interrupt reply ID? */
	if (oh.unique & FUSE_INT_REQ_BIT) {
		__fuse_get_request(req);
		spin_unlock(&fpq->lock);

		err = 0;
		if (nbytes != sizeof(struct fuse_out_header))
			err = -EINVAL;
		else if (oh.error == -ENOSYS)
			fc->no_interrupt = 1;
		else if (oh.error == -EAGAIN)
			err = queue_interrupt(&fc->iq, req);

		fuse_put_request(fc, req);

		goto copy_finish;
	}

	clear_bit(FR_SENT, &req->flags);
	list_move(&req->list, &fpq->io);
	req->out.h = oh;
	set_bit(FR_LOCKED, &req->flags);
	spin_unlock(&fpq->lock);
	cs->req = req;
	if (!req->args->page_replace)
		cs->move_pages = 0;

	if (oh.error)
		err = nbytes != sizeof(oh) ? -EINVAL : 0;
	else
		err = copy_out_args(cs, req->args, nbytes);
	fuse_copy_finish(cs);

	spin_lock(&fpq->lock);
	clear_bit(FR_LOCKED, &req->flags);
	if (!fpq->connected)
		err = -ENOENT;
	else if (err)
		req->out.h.error = -EIO;
	if (!test_bit(FR_PRIVATE, &req->flags))
		list_del_init(&req->list);
	spin_unlock(&fpq->lock);

	fuse_request_end(fc, req);
out:
	return err ? err : nbytes;

copy_finish:
	fuse_copy_finish(cs);
	goto out;
}