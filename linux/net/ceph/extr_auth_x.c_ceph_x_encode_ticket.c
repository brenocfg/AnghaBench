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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ceph_x_ticket_handler {TYPE_1__* ticket_blob; int /*<<< orphan*/  secret_id; } ;
struct TYPE_4__ {char* iov_base; int /*<<< orphan*/  iov_len; } ;
struct TYPE_3__ {TYPE_2__ vec; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  bad ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_encode_32_safe (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_encode_64 (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_encode_8 (void**,int) ; 
 int /*<<< orphan*/  ceph_encode_copy_safe (void**,void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ceph_x_encode_ticket(struct ceph_x_ticket_handler *th,
				void **p, void *end)
{
	ceph_decode_need(p, end, 1 + sizeof(u64), bad);
	ceph_encode_8(p, 1);
	ceph_encode_64(p, th->secret_id);
	if (th->ticket_blob) {
		const char *buf = th->ticket_blob->vec.iov_base;
		u32 len = th->ticket_blob->vec.iov_len;

		ceph_encode_32_safe(p, end, len, bad);
		ceph_encode_copy_safe(p, end, buf, len, bad);
	} else {
		ceph_encode_32_safe(p, end, 0, bad);
	}

	return 0;
bad:
	return -ERANGE;
}