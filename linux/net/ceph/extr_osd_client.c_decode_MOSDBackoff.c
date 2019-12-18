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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int iov_len; void* iov_base; } ;
struct ceph_msg {TYPE_1__ front; } ;
struct TYPE_4__ {int /*<<< orphan*/  shard; int /*<<< orphan*/  pgid; } ;
struct MOSDBackoff {void* end; void* begin; int /*<<< orphan*/  id; int /*<<< orphan*/  op; int /*<<< orphan*/  map_epoch; TYPE_2__ spgid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_64_safe (void**,void* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_8_safe (void**,void* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ceph_decode_pgid (void**,void* const,int /*<<< orphan*/ *) ; 
 int ceph_start_decoding (void**,void* const,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_hoid (void**,void* const,void*) ; 
 int /*<<< orphan*/  e_inval ; 
 int /*<<< orphan*/  free_hoid (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_MOSDBackoff(const struct ceph_msg *msg, struct MOSDBackoff *m)
{
	void *p = msg->front.iov_base;
	void *const end = p + msg->front.iov_len;
	u8 struct_v;
	u32 struct_len;
	int ret;

	ret = ceph_start_decoding(&p, end, 1, "spg_t", &struct_v, &struct_len);
	if (ret)
		return ret;

	ret = ceph_decode_pgid(&p, end, &m->spgid.pgid);
	if (ret)
		return ret;

	ceph_decode_8_safe(&p, end, m->spgid.shard, e_inval);
	ceph_decode_32_safe(&p, end, m->map_epoch, e_inval);
	ceph_decode_8_safe(&p, end, m->op, e_inval);
	ceph_decode_64_safe(&p, end, m->id, e_inval);

	m->begin = kzalloc(sizeof(*m->begin), GFP_NOIO);
	if (!m->begin)
		return -ENOMEM;

	ret = decode_hoid(&p, end, m->begin);
	if (ret) {
		free_hoid(m->begin);
		return ret;
	}

	m->end = kzalloc(sizeof(*m->end), GFP_NOIO);
	if (!m->end) {
		free_hoid(m->begin);
		return -ENOMEM;
	}

	ret = decode_hoid(&p, end, m->end);
	if (ret) {
		free_hoid(m->begin);
		free_hoid(m->end);
		return ret;
	}

	return 0;

e_inval:
	return -EINVAL;
}