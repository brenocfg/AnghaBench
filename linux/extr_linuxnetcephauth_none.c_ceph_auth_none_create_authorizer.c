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
struct TYPE_2__ {int /*<<< orphan*/  destroy; } ;
struct ceph_none_authorizer {int /*<<< orphan*/  reply_buf; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  buf; TYPE_1__ base; } ;
struct ceph_authorizer {int dummy; } ;
struct ceph_auth_handshake {int authorizer_reply_buf_len; int /*<<< orphan*/  authorizer_reply_buf; int /*<<< orphan*/  authorizer_buf_len; int /*<<< orphan*/  authorizer_buf; struct ceph_authorizer* authorizer; } ;
struct ceph_auth_client {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int ceph_auth_none_build_authorizer (struct ceph_auth_client*,struct ceph_none_authorizer*) ; 
 int /*<<< orphan*/  ceph_auth_none_destroy_authorizer ; 
 int /*<<< orphan*/  kfree (struct ceph_none_authorizer*) ; 
 struct ceph_none_authorizer* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ceph_auth_none_create_authorizer(
	struct ceph_auth_client *ac, int peer_type,
	struct ceph_auth_handshake *auth)
{
	struct ceph_none_authorizer *au;
	int ret;

	au = kmalloc(sizeof(*au), GFP_NOFS);
	if (!au)
		return -ENOMEM;

	au->base.destroy = ceph_auth_none_destroy_authorizer;

	ret = ceph_auth_none_build_authorizer(ac, au);
	if (ret) {
		kfree(au);
		return ret;
	}

	auth->authorizer = (struct ceph_authorizer *) au;
	auth->authorizer_buf = au->buf;
	auth->authorizer_buf_len = au->buf_len;
	auth->authorizer_reply_buf = au->reply_buf;
	auth->authorizer_reply_buf_len = sizeof (au->reply_buf);

	return 0;
}