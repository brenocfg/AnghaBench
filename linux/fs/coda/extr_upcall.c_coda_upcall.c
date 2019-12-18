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
struct TYPE_3__ {int result; } ;
union outputArgs {TYPE_1__ oh; } ;
struct TYPE_4__ {scalar_t__ unique; int /*<<< orphan*/  opcode; } ;
union inputArgs {TYPE_2__ ih; } ;
struct venus_comm {int /*<<< orphan*/  vc_mutex; int /*<<< orphan*/  vc_waitq; int /*<<< orphan*/  vc_pending; int /*<<< orphan*/  vc_inuse; scalar_t__ vc_seq; } ;
struct upc_req {int uc_flags; int uc_inSize; int uc_outSize; int /*<<< orphan*/  uc_chain; void* uc_data; scalar_t__ uc_unique; int /*<<< orphan*/  uc_opcode; int /*<<< orphan*/  uc_sleep; } ;
struct coda_in_hdr {int dummy; } ;

/* Variables and functions */
 int CODA_REQ_ABORT ; 
 int CODA_REQ_ASYNC ; 
 int CODA_REQ_READ ; 
 int CODA_REQ_WRITE ; 
 int /*<<< orphan*/  CODA_SIGNAL ; 
 int EINTR ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  coda_waitfor_upcall (struct venus_comm*,struct upc_req*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct upc_req*) ; 
 struct upc_req* kmalloc (int,int /*<<< orphan*/ ) ; 
 union inputArgs* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int coda_upcall(struct venus_comm *vcp,
		       int inSize, int *outSize,
		       union inputArgs *buffer)
{
	union outputArgs *out;
	union inputArgs *sig_inputArgs;
	struct upc_req *req = NULL, *sig_req;
	int error;

	mutex_lock(&vcp->vc_mutex);

	if (!vcp->vc_inuse) {
		pr_notice("Venus dead, not sending upcall\n");
		error = -ENXIO;
		goto exit;
	}

	/* Format the request message. */
	req = kmalloc(sizeof(struct upc_req), GFP_KERNEL);
	if (!req) {
		error = -ENOMEM;
		goto exit;
	}

	buffer->ih.unique = ++vcp->vc_seq;

	req->uc_data = (void *)buffer;
	req->uc_flags = outSize ? 0 : CODA_REQ_ASYNC;
	req->uc_inSize = inSize;
	req->uc_outSize = (outSize && *outSize) ? *outSize : inSize;
	req->uc_opcode = buffer->ih.opcode;
	req->uc_unique = buffer->ih.unique;
	init_waitqueue_head(&req->uc_sleep);

	/* Append msg to pending queue and poke Venus. */
	list_add_tail(&req->uc_chain, &vcp->vc_pending);
	wake_up_interruptible(&vcp->vc_waitq);

	if (req->uc_flags & CODA_REQ_ASYNC) {
		mutex_unlock(&vcp->vc_mutex);
		return 0;
	}

	/* We can be interrupted while we wait for Venus to process
	 * our request.  If the interrupt occurs before Venus has read
	 * the request, we dequeue and return. If it occurs after the
	 * read but before the reply, we dequeue, send a signal
	 * message, and return. If it occurs after the reply we ignore
	 * it. In no case do we want to restart the syscall.  If it
	 * was interrupted by a venus shutdown (psdev_close), return
	 * ENODEV.  */

	/* Go to sleep.  Wake up on signals only after the timeout. */
	coda_waitfor_upcall(vcp, req);

	/* Op went through, interrupt or not... */
	if (req->uc_flags & CODA_REQ_WRITE) {
		out = (union outputArgs *)req->uc_data;
		/* here we map positive Venus errors to kernel errors */
		error = -out->oh.result;
		*outSize = req->uc_outSize;
		goto exit;
	}

	error = -EINTR;
	if ((req->uc_flags & CODA_REQ_ABORT) || !signal_pending(current)) {
		pr_warn("Unexpected interruption.\n");
		goto exit;
	}

	/* Interrupted before venus read it. */
	if (!(req->uc_flags & CODA_REQ_READ))
		goto exit;

	/* Venus saw the upcall, make sure we can send interrupt signal */
	if (!vcp->vc_inuse) {
		pr_info("Venus dead, not sending signal.\n");
		goto exit;
	}

	error = -ENOMEM;
	sig_req = kmalloc(sizeof(struct upc_req), GFP_KERNEL);
	if (!sig_req) goto exit;

	sig_inputArgs = kvzalloc(sizeof(struct coda_in_hdr), GFP_KERNEL);
	if (!sig_inputArgs) {
		kfree(sig_req);
		goto exit;
	}

	error = -EINTR;
	sig_inputArgs->ih.opcode = CODA_SIGNAL;
	sig_inputArgs->ih.unique = req->uc_unique;

	sig_req->uc_flags = CODA_REQ_ASYNC;
	sig_req->uc_opcode = sig_inputArgs->ih.opcode;
	sig_req->uc_unique = sig_inputArgs->ih.unique;
	sig_req->uc_data = (void *)sig_inputArgs;
	sig_req->uc_inSize = sizeof(struct coda_in_hdr);
	sig_req->uc_outSize = sizeof(struct coda_in_hdr);

	/* insert at head of queue! */
	list_add(&(sig_req->uc_chain), &vcp->vc_pending);
	wake_up_interruptible(&vcp->vc_waitq);

exit:
	kfree(req);
	mutex_unlock(&vcp->vc_mutex);
	return error;
}