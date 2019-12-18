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
struct ceph_entity_addr {int dummy; } ;
struct ceph_options {struct ceph_entity_addr my_addr; } ;
struct ceph_client {int /*<<< orphan*/  msgr; int /*<<< orphan*/  monc; int /*<<< orphan*/  osdc; struct ceph_options* options; int /*<<< orphan*/  required_features; int /*<<< orphan*/  supported_features; int /*<<< orphan*/ * extra_mon_dispatch; scalar_t__ auth_err; int /*<<< orphan*/  auth_wq; int /*<<< orphan*/  mount_mutex; void* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_FEATURES_REQUIRED_DEFAULT ; 
 int /*<<< orphan*/  CEPH_FEATURES_SUPPORTED_DEFAULT ; 
 int /*<<< orphan*/  CEPH_FEATURE_MSG_AUTH ; 
 int ENOMEM ; 
 struct ceph_client* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MYIP ; 
 int /*<<< orphan*/  NOMSGAUTH ; 
 int /*<<< orphan*/  ceph_messenger_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_messenger_init (int /*<<< orphan*/ *,struct ceph_entity_addr*) ; 
 int ceph_monc_init (int /*<<< orphan*/ *,struct ceph_client*) ; 
 int /*<<< orphan*/  ceph_monc_stop (int /*<<< orphan*/ *) ; 
 int ceph_osdc_init (int /*<<< orphan*/ *,struct ceph_client*) ; 
 scalar_t__ ceph_test_opt (struct ceph_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ceph_client*) ; 
 struct ceph_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int wait_for_random_bytes () ; 

struct ceph_client *ceph_create_client(struct ceph_options *opt, void *private)
{
	struct ceph_client *client;
	struct ceph_entity_addr *myaddr = NULL;
	int err;

	err = wait_for_random_bytes();
	if (err < 0)
		return ERR_PTR(err);

	client = kzalloc(sizeof(*client), GFP_KERNEL);
	if (client == NULL)
		return ERR_PTR(-ENOMEM);

	client->private = private;
	client->options = opt;

	mutex_init(&client->mount_mutex);
	init_waitqueue_head(&client->auth_wq);
	client->auth_err = 0;

	client->extra_mon_dispatch = NULL;
	client->supported_features = CEPH_FEATURES_SUPPORTED_DEFAULT;
	client->required_features = CEPH_FEATURES_REQUIRED_DEFAULT;

	if (!ceph_test_opt(client, NOMSGAUTH))
		client->required_features |= CEPH_FEATURE_MSG_AUTH;

	/* msgr */
	if (ceph_test_opt(client, MYIP))
		myaddr = &client->options->my_addr;

	ceph_messenger_init(&client->msgr, myaddr);

	/* subsystems */
	err = ceph_monc_init(&client->monc, client);
	if (err < 0)
		goto fail;
	err = ceph_osdc_init(&client->osdc, client);
	if (err < 0)
		goto fail_monc;

	return client;

fail_monc:
	ceph_monc_stop(&client->monc);
fail:
	ceph_messenger_fini(&client->msgr);
	kfree(client);
	return ERR_PTR(err);
}