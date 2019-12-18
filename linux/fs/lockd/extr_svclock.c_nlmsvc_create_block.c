#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct svc_rqst {int /*<<< orphan*/  rq_server; } ;
struct TYPE_4__ {int /*<<< orphan*/ * fl_lmops; int /*<<< orphan*/  fl_flags; } ;
struct TYPE_5__ {TYPE_1__ fl; } ;
struct TYPE_6__ {int /*<<< orphan*/  cookie; TYPE_2__ lock; } ;
struct nlm_rqst {struct nlm_block* a_block; int /*<<< orphan*/  a_flags; TYPE_3__ a_args; } ;
struct nlm_lock {int dummy; } ;
struct nlm_host {int dummy; } ;
struct nlm_file {int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_count; } ;
struct nlm_cookie {int dummy; } ;
struct nlm_block {struct nlm_rqst* b_call; int /*<<< orphan*/  b_flist; struct nlm_file* b_file; struct nlm_host* b_host; int /*<<< orphan*/  b_daemon; int /*<<< orphan*/  b_list; int /*<<< orphan*/  b_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  FL_SLEEP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_TASK_ASYNC ; 
 int /*<<< orphan*/  dprintk (char*,struct nlm_block*) ; 
 int /*<<< orphan*/  kfree (struct nlm_block*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct nlm_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nlm_rqst* nlm_alloc_call (struct nlm_host*) ; 
 int /*<<< orphan*/  nlmclnt_next_cookie (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmsvc_lock_operations ; 
 int /*<<< orphan*/  nlmsvc_release_call (struct nlm_rqst*) ; 
 int /*<<< orphan*/  nlmsvc_setgrantargs (struct nlm_rqst*,struct nlm_lock*) ; 

__attribute__((used)) static struct nlm_block *
nlmsvc_create_block(struct svc_rqst *rqstp, struct nlm_host *host,
		    struct nlm_file *file, struct nlm_lock *lock,
		    struct nlm_cookie *cookie)
{
	struct nlm_block	*block;
	struct nlm_rqst		*call = NULL;

	call = nlm_alloc_call(host);
	if (call == NULL)
		return NULL;

	/* Allocate memory for block, and initialize arguments */
	block = kzalloc(sizeof(*block), GFP_KERNEL);
	if (block == NULL)
		goto failed;
	kref_init(&block->b_count);
	INIT_LIST_HEAD(&block->b_list);
	INIT_LIST_HEAD(&block->b_flist);

	if (!nlmsvc_setgrantargs(call, lock))
		goto failed_free;

	/* Set notifier function for VFS, and init args */
	call->a_args.lock.fl.fl_flags |= FL_SLEEP;
	call->a_args.lock.fl.fl_lmops = &nlmsvc_lock_operations;
	nlmclnt_next_cookie(&call->a_args.cookie);

	dprintk("lockd: created block %p...\n", block);

	/* Create and initialize the block */
	block->b_daemon = rqstp->rq_server;
	block->b_host   = host;
	block->b_file   = file;
	file->f_count++;

	/* Add to file's list of blocks */
	list_add(&block->b_flist, &file->f_blocks);

	/* Set up RPC arguments for callback */
	block->b_call = call;
	call->a_flags   = RPC_TASK_ASYNC;
	call->a_block = block;

	return block;

failed_free:
	kfree(block);
failed:
	nlmsvc_release_call(call);
	return NULL;
}