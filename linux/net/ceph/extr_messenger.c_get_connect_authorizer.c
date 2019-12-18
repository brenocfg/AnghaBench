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
struct TYPE_3__ {void* authorizer_len; void* authorizer_protocol; } ;
struct ceph_connection {TYPE_1__ out_connect; struct ceph_auth_handshake* auth; int /*<<< orphan*/  auth_retry; TYPE_2__* ops; } ;
struct ceph_auth_handshake {int authorizer_buf_len; } ;
struct TYPE_4__ {struct ceph_auth_handshake* (* get_authorizer ) (struct ceph_connection*,int*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 void* CEPH_AUTH_UNKNOWN ; 
 scalar_t__ IS_ERR (struct ceph_auth_handshake*) ; 
 int PTR_ERR (struct ceph_auth_handshake*) ; 
 void* cpu_to_le32 (int) ; 
 struct ceph_auth_handshake* stub1 (struct ceph_connection*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_connect_authorizer(struct ceph_connection *con)
{
	struct ceph_auth_handshake *auth;
	int auth_proto;

	if (!con->ops->get_authorizer) {
		con->auth = NULL;
		con->out_connect.authorizer_protocol = CEPH_AUTH_UNKNOWN;
		con->out_connect.authorizer_len = 0;
		return 0;
	}

	auth = con->ops->get_authorizer(con, &auth_proto, con->auth_retry);
	if (IS_ERR(auth))
		return PTR_ERR(auth);

	con->auth = auth;
	con->out_connect.authorizer_protocol = cpu_to_le32(auth_proto);
	con->out_connect.authorizer_len = cpu_to_le32(auth->authorizer_buf_len);
	return 0;
}