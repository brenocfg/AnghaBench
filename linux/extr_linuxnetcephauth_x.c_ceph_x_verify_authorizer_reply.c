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
struct ceph_x_authorizer {scalar_t__ nonce; int /*<<< orphan*/  session_key; void* enc_buf; } ;
struct ceph_x_authorize_reply {int /*<<< orphan*/  nonce_plus_one; } ;
struct ceph_authorizer {int dummy; } ;
struct ceph_auth_client {int dummy; } ;

/* Variables and functions */
 int CEPHX_AU_ENC_BUF_LEN ; 
 int EINVAL ; 
 int EPERM ; 
 int ceph_x_decrypt (int /*<<< orphan*/ *,void**,void*) ; 
 int ceph_x_encrypt_offset () ; 
 int /*<<< orphan*/  dout (char*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int ceph_x_verify_authorizer_reply(struct ceph_auth_client *ac,
					  struct ceph_authorizer *a)
{
	struct ceph_x_authorizer *au = (void *)a;
	void *p = au->enc_buf;
	struct ceph_x_authorize_reply *reply = p + ceph_x_encrypt_offset();
	int ret;

	ret = ceph_x_decrypt(&au->session_key, &p, p + CEPHX_AU_ENC_BUF_LEN);
	if (ret < 0)
		return ret;
	if (ret < sizeof(*reply)) {
		pr_err("bad size %d for ceph_x_authorize_reply\n", ret);
		return -EINVAL;
	}

	if (au->nonce + 1 != le64_to_cpu(reply->nonce_plus_one))
		ret = -EPERM;
	else
		ret = 0;
	dout("verify_authorizer_reply nonce %llx got %llx ret %d\n",
	     au->nonce, le64_to_cpu(reply->nonce_plus_one), ret);
	return ret;
}