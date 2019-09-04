#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct p9_client {int msize; int /*<<< orphan*/  tagpool; TYPE_1__* trans_mod; int /*<<< orphan*/  proto_version; int /*<<< orphan*/  fids; int /*<<< orphan*/  lock; int /*<<< orphan*/  name; int /*<<< orphan*/ * trans; } ;
struct TYPE_5__ {char* nodename; } ;
struct TYPE_4__ {int (* create ) (struct p9_client*,char const*,char*) ;int maxsize; int /*<<< orphan*/  (* close ) (struct p9_client*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 struct p9_client* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 int /*<<< orphan*/  P9_DEBUG_MUX ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct p9_client*) ; 
 struct p9_client* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int p9_client_version (struct p9_client*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  p9_idpool_destroy (int /*<<< orphan*/ ) ; 
 int p9_tag_init (struct p9_client*) ; 
 int parse_opts (char*,struct p9_client*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 
 int stub1 (struct p9_client*,char const*,char*) ; 
 int /*<<< orphan*/  stub2 (struct p9_client*) ; 
 TYPE_3__* utsname () ; 
 TYPE_1__* v9fs_get_default_trans () ; 
 int /*<<< orphan*/  v9fs_put_trans (TYPE_1__*) ; 

struct p9_client *p9_client_create(const char *dev_name, char *options)
{
	int err;
	struct p9_client *clnt;
	char *client_id;

	err = 0;
	clnt = kmalloc(sizeof(struct p9_client), GFP_KERNEL);
	if (!clnt)
		return ERR_PTR(-ENOMEM);

	clnt->trans_mod = NULL;
	clnt->trans = NULL;

	client_id = utsname()->nodename;
	memcpy(clnt->name, client_id, strlen(client_id) + 1);

	spin_lock_init(&clnt->lock);
	idr_init(&clnt->fids);

	err = p9_tag_init(clnt);
	if (err < 0)
		goto free_client;

	err = parse_opts(options, clnt);
	if (err < 0)
		goto destroy_tagpool;

	if (!clnt->trans_mod)
		clnt->trans_mod = v9fs_get_default_trans();

	if (clnt->trans_mod == NULL) {
		err = -EPROTONOSUPPORT;
		p9_debug(P9_DEBUG_ERROR,
			 "No transport defined or default transport\n");
		goto destroy_tagpool;
	}

	p9_debug(P9_DEBUG_MUX, "clnt %p trans %p msize %d protocol %d\n",
		 clnt, clnt->trans_mod, clnt->msize, clnt->proto_version);

	err = clnt->trans_mod->create(clnt, dev_name, options);
	if (err)
		goto put_trans;

	if (clnt->msize > clnt->trans_mod->maxsize)
		clnt->msize = clnt->trans_mod->maxsize;

	if (clnt->msize < 4096) {
		p9_debug(P9_DEBUG_ERROR,
			 "Please specify a msize of at least 4k\n");
		err = -EINVAL;
		goto close_trans;
	}

	err = p9_client_version(clnt);
	if (err)
		goto close_trans;

	return clnt;

close_trans:
	clnt->trans_mod->close(clnt);
put_trans:
	v9fs_put_trans(clnt->trans_mod);
destroy_tagpool:
	p9_idpool_destroy(clnt->tagpool);
free_client:
	kfree(clnt);
	return ERR_PTR(err);
}