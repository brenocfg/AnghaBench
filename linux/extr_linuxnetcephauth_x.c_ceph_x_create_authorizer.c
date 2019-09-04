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
struct ceph_x_ticket_handler {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  destroy; } ;
struct ceph_x_authorizer {int /*<<< orphan*/  enc_buf; TYPE_3__* buf; TYPE_1__ base; } ;
struct ceph_authorizer {int dummy; } ;
struct ceph_auth_handshake {int /*<<< orphan*/  check_message_signature; int /*<<< orphan*/  sign_message; int /*<<< orphan*/  authorizer_reply_buf_len; int /*<<< orphan*/  authorizer_reply_buf; int /*<<< orphan*/  authorizer_buf_len; int /*<<< orphan*/  authorizer_buf; struct ceph_authorizer* authorizer; } ;
struct ceph_auth_client {TYPE_4__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  check_message_signature; int /*<<< orphan*/  sign_message; } ;
struct TYPE_6__ {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct TYPE_7__ {TYPE_2__ vec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPHX_AU_ENC_BUF_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct ceph_x_ticket_handler*) ; 
 int PTR_ERR (struct ceph_x_ticket_handler*) ; 
 int ceph_x_build_authorizer (struct ceph_auth_client*,struct ceph_x_ticket_handler*,struct ceph_x_authorizer*) ; 
 int /*<<< orphan*/  ceph_x_destroy_authorizer ; 
 struct ceph_x_ticket_handler* get_ticket_handler (struct ceph_auth_client*,int) ; 
 int /*<<< orphan*/  kfree (struct ceph_x_authorizer*) ; 
 struct ceph_x_authorizer* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ceph_x_create_authorizer(
	struct ceph_auth_client *ac, int peer_type,
	struct ceph_auth_handshake *auth)
{
	struct ceph_x_authorizer *au;
	struct ceph_x_ticket_handler *th;
	int ret;

	th = get_ticket_handler(ac, peer_type);
	if (IS_ERR(th))
		return PTR_ERR(th);

	au = kzalloc(sizeof(*au), GFP_NOFS);
	if (!au)
		return -ENOMEM;

	au->base.destroy = ceph_x_destroy_authorizer;

	ret = ceph_x_build_authorizer(ac, th, au);
	if (ret) {
		kfree(au);
		return ret;
	}

	auth->authorizer = (struct ceph_authorizer *) au;
	auth->authorizer_buf = au->buf->vec.iov_base;
	auth->authorizer_buf_len = au->buf->vec.iov_len;
	auth->authorizer_reply_buf = au->enc_buf;
	auth->authorizer_reply_buf_len = CEPHX_AU_ENC_BUF_LEN;
	auth->sign_message = ac->ops->sign_message;
	auth->check_message_signature = ac->ops->check_message_signature;

	return 0;
}