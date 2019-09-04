#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  authorizer; } ;
struct ceph_mds_session {TYPE_4__ s_auth; struct ceph_mds_client* s_mdsc; } ;
struct ceph_mds_client {TYPE_3__* fsc; } ;
struct ceph_connection {struct ceph_mds_session* private; } ;
struct ceph_auth_client {int dummy; } ;
struct TYPE_7__ {TYPE_2__* client; } ;
struct TYPE_5__ {struct ceph_auth_client* auth; } ;
struct TYPE_6__ {TYPE_1__ monc; } ;

/* Variables and functions */
 int ceph_auth_add_authorizer_challenge (struct ceph_auth_client*,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int add_authorizer_challenge(struct ceph_connection *con,
				    void *challenge_buf, int challenge_buf_len)
{
	struct ceph_mds_session *s = con->private;
	struct ceph_mds_client *mdsc = s->s_mdsc;
	struct ceph_auth_client *ac = mdsc->fsc->client->monc.auth;

	return ceph_auth_add_authorizer_challenge(ac, s->s_auth.authorizer,
					    challenge_buf, challenge_buf_len);
}