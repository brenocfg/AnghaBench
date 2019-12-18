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
struct user_namespace {int dummy; } ;
struct nfs_server {TYPE_1__* client; } ;
struct TYPE_4__ {struct user_namespace* user_ns; } ;
struct TYPE_3__ {TYPE_2__* cl_cred; } ;

/* Variables and functions */
 struct user_namespace init_user_ns ; 

__attribute__((used)) static int nfs_compare_userns(const struct nfs_server *old,
		const struct nfs_server *new)
{
	const struct user_namespace *oldns = &init_user_ns;
	const struct user_namespace *newns = &init_user_ns;

	if (old->client && old->client->cl_cred)
		oldns = old->client->cl_cred->user_ns;
	if (new->client && new->client->cl_cred)
		newns = new->client->cl_cred->user_ns;
	if (oldns != newns)
		return 0;
	return 1;
}