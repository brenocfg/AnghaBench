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
typedef  int /*<<< orphan*/  u64 ;
struct ceph_x_encrypt_header {int dummy; } ;
struct ceph_x_authorizer {int /*<<< orphan*/  session_key; } ;
struct ceph_x_authorize_challenge {int /*<<< orphan*/  server_challenge; } ;

/* Variables and functions */
 int EINVAL ; 
 int __ceph_x_decrypt (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int decrypt_authorize_challenge(struct ceph_x_authorizer *au,
				       void *challenge_buf,
				       int challenge_buf_len,
				       u64 *server_challenge)
{
	struct ceph_x_authorize_challenge *ch =
	    challenge_buf + sizeof(struct ceph_x_encrypt_header);
	int ret;

	/* no leading len */
	ret = __ceph_x_decrypt(&au->session_key, challenge_buf,
			       challenge_buf_len);
	if (ret < 0)
		return ret;
	if (ret < sizeof(*ch)) {
		pr_err("bad size %d for ceph_x_authorize_challenge\n", ret);
		return -EINVAL;
	}

	*server_challenge = le64_to_cpu(ch->server_challenge);
	return 0;
}