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
struct ceph_mds_session {struct ceph_mds_client* s_mdsc; } ;
struct ceph_mds_client {TYPE_2__* fsc; } ;
struct ceph_connection {struct ceph_mds_session* private; } ;
struct ceph_auth_client {int dummy; } ;
struct TYPE_6__ {struct ceph_auth_client* auth; } ;
struct TYPE_5__ {TYPE_1__* client; } ;
struct TYPE_4__ {TYPE_3__ monc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_ENTITY_TYPE_MDS ; 
 int /*<<< orphan*/  ceph_auth_invalidate_authorizer (struct ceph_auth_client*,int /*<<< orphan*/ ) ; 
 int ceph_monc_validate_auth (TYPE_3__*) ; 

__attribute__((used)) static int invalidate_authorizer(struct ceph_connection *con)
{
	struct ceph_mds_session *s = con->private;
	struct ceph_mds_client *mdsc = s->s_mdsc;
	struct ceph_auth_client *ac = mdsc->fsc->client->monc.auth;

	ceph_auth_invalidate_authorizer(ac, CEPH_ENTITY_TYPE_MDS);

	return ceph_monc_validate_auth(&mdsc->fsc->client->monc);
}