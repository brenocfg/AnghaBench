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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ceph_crypto_key {int dummy; } ;
struct ceph_auth_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bad ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_8_safe (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ) ; 
 int process_one_ticket (struct ceph_auth_client*,struct ceph_crypto_key*,void**,void*) ; 

__attribute__((used)) static int ceph_x_proc_ticket_reply(struct ceph_auth_client *ac,
				    struct ceph_crypto_key *secret,
				    void *buf, void *end)
{
	void *p = buf;
	u8 reply_struct_v;
	u32 num;
	int ret;

	ceph_decode_8_safe(&p, end, reply_struct_v, bad);
	if (reply_struct_v != 1)
		return -EINVAL;

	ceph_decode_32_safe(&p, end, num, bad);
	dout("%d tickets\n", num);

	while (num--) {
		ret = process_one_ticket(ac, secret, &p, end);
		if (ret)
			return ret;
	}

	return 0;

bad:
	return -EINVAL;
}