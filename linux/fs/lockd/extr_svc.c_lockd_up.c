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
struct svc_serv {int dummy; } ;
struct net {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct svc_serv*) ; 
 int PTR_ERR (struct svc_serv*) ; 
 struct svc_serv* lockd_create_svc () ; 
 int /*<<< orphan*/  lockd_down_net (struct svc_serv*,struct net*) ; 
 int lockd_start_svc (struct svc_serv*) ; 
 int /*<<< orphan*/  lockd_unregister_notifiers () ; 
 int lockd_up_net (struct svc_serv*,struct net*,struct cred const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmsvc_mutex ; 
 int /*<<< orphan*/  nlmsvc_users ; 
 int /*<<< orphan*/  svc_destroy (struct svc_serv*) ; 

int lockd_up(struct net *net, const struct cred *cred)
{
	struct svc_serv *serv;
	int error;

	mutex_lock(&nlmsvc_mutex);

	serv = lockd_create_svc();
	if (IS_ERR(serv)) {
		error = PTR_ERR(serv);
		goto err_create;
	}

	error = lockd_up_net(serv, net, cred);
	if (error < 0) {
		lockd_unregister_notifiers();
		goto err_put;
	}

	error = lockd_start_svc(serv);
	if (error < 0) {
		lockd_down_net(serv, net);
		goto err_put;
	}
	nlmsvc_users++;
	/*
	 * Note: svc_serv structures have an initial use count of 1,
	 * so we exit through here on both success and failure.
	 */
err_put:
	svc_destroy(serv);
err_create:
	mutex_unlock(&nlmsvc_mutex);
	return error;
}