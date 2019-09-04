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
struct rpc_pipe_msg {int dummy; } ;
struct request_key_auth {struct key* target_key; } ;
struct key {int /*<<< orphan*/  description; } ;
struct idmap_msg {int dummy; } ;
struct idmap_legacy_upcalldata {int /*<<< orphan*/  authkey; struct idmap* idmap; struct idmap_msg idmap_msg; struct rpc_pipe_msg pipe_msg; } ;
struct idmap {int /*<<< orphan*/  idmap_pipe; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOKEY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  complete_request_key (struct key*,int) ; 
 struct request_key_auth* get_request_key_auth (struct key*) ; 
 int /*<<< orphan*/  key_get (struct key*) ; 
 int /*<<< orphan*/  kfree (struct idmap_legacy_upcalldata*) ; 
 struct idmap_legacy_upcalldata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_idmap_abort_pipe_upcall (struct idmap*,int) ; 
 int nfs_idmap_prepare_message (int /*<<< orphan*/ ,struct idmap*,struct idmap_msg*,struct rpc_pipe_msg*) ; 
 int /*<<< orphan*/  nfs_idmap_prepare_pipe_upcall (struct idmap*,struct idmap_legacy_upcalldata*) ; 
 int rpc_queue_upcall (int /*<<< orphan*/ ,struct rpc_pipe_msg*) ; 

__attribute__((used)) static int nfs_idmap_legacy_upcall(struct key *authkey, void *aux)
{
	struct idmap_legacy_upcalldata *data;
	struct request_key_auth *rka = get_request_key_auth(authkey);
	struct rpc_pipe_msg *msg;
	struct idmap_msg *im;
	struct idmap *idmap = (struct idmap *)aux;
	struct key *key = rka->target_key;
	int ret = -ENOKEY;

	if (!aux)
		goto out1;

	/* msg and im are freed in idmap_pipe_destroy_msg */
	ret = -ENOMEM;
	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		goto out1;

	msg = &data->pipe_msg;
	im = &data->idmap_msg;
	data->idmap = idmap;
	data->authkey = key_get(authkey);

	ret = nfs_idmap_prepare_message(key->description, idmap, im, msg);
	if (ret < 0)
		goto out2;

	ret = -EAGAIN;
	if (!nfs_idmap_prepare_pipe_upcall(idmap, data))
		goto out2;

	ret = rpc_queue_upcall(idmap->idmap_pipe, msg);
	if (ret < 0)
		nfs_idmap_abort_pipe_upcall(idmap, ret);

	return ret;
out2:
	kfree(data);
out1:
	complete_request_key(authkey, ret);
	return ret;
}