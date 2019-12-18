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
struct gss_upcall_msg {int /*<<< orphan*/  service_name; struct gss_auth* auth; int /*<<< orphan*/  uid; int /*<<< orphan*/  count; int /*<<< orphan*/  waitqueue; int /*<<< orphan*/  rpc_waitqueue; int /*<<< orphan*/  list; int /*<<< orphan*/  pipe; } ;
struct gss_auth {int /*<<< orphan*/  net; int /*<<< orphan*/  kref; TYPE_1__** gss_pipe; } ;
typedef  int /*<<< orphan*/  kuid_t ;
struct TYPE_2__ {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct gss_upcall_msg* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int get_pipe_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gss_upcall_msg*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kstrdup_const (char const*,int /*<<< orphan*/ ) ; 
 struct gss_upcall_msg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pipe_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rpc_init_wait_queue (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static struct gss_upcall_msg *
gss_alloc_msg(struct gss_auth *gss_auth,
		kuid_t uid, const char *service_name)
{
	struct gss_upcall_msg *gss_msg;
	int vers;
	int err = -ENOMEM;

	gss_msg = kzalloc(sizeof(*gss_msg), GFP_NOFS);
	if (gss_msg == NULL)
		goto err;
	vers = get_pipe_version(gss_auth->net);
	err = vers;
	if (err < 0)
		goto err_free_msg;
	gss_msg->pipe = gss_auth->gss_pipe[vers]->pipe;
	INIT_LIST_HEAD(&gss_msg->list);
	rpc_init_wait_queue(&gss_msg->rpc_waitqueue, "RPCSEC_GSS upcall waitq");
	init_waitqueue_head(&gss_msg->waitqueue);
	refcount_set(&gss_msg->count, 1);
	gss_msg->uid = uid;
	gss_msg->auth = gss_auth;
	kref_get(&gss_auth->kref);
	if (service_name) {
		gss_msg->service_name = kstrdup_const(service_name, GFP_NOFS);
		if (!gss_msg->service_name) {
			err = -ENOMEM;
			goto err_put_pipe_version;
		}
	}
	return gss_msg;
err_put_pipe_version:
	put_pipe_version(gss_auth->net);
err_free_msg:
	kfree(gss_msg);
err:
	return ERR_PTR(err);
}