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
struct TYPE_4__ {int iov_len; int /*<<< orphan*/ * iov_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  front_len; void* priority; void* type; } ;
struct ceph_msg {int front_alloc_len; TYPE_2__ front; int /*<<< orphan*/  data; int /*<<< orphan*/  kref; int /*<<< orphan*/  list_head; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int CEPH_MSG_PRIO_DEFAULT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/ * ceph_kvmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_msg_cache ; 
 int /*<<< orphan*/  ceph_msg_put (struct ceph_msg*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 struct ceph_msg* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

struct ceph_msg *ceph_msg_new(int type, int front_len, gfp_t flags,
			      bool can_fail)
{
	struct ceph_msg *m;

	m = kmem_cache_zalloc(ceph_msg_cache, flags);
	if (m == NULL)
		goto out;

	m->hdr.type = cpu_to_le16(type);
	m->hdr.priority = cpu_to_le16(CEPH_MSG_PRIO_DEFAULT);
	m->hdr.front_len = cpu_to_le32(front_len);

	INIT_LIST_HEAD(&m->list_head);
	kref_init(&m->kref);
	INIT_LIST_HEAD(&m->data);

	/* front */
	if (front_len) {
		m->front.iov_base = ceph_kvmalloc(front_len, flags);
		if (m->front.iov_base == NULL) {
			dout("ceph_msg_new can't allocate %d bytes\n",
			     front_len);
			goto out2;
		}
	} else {
		m->front.iov_base = NULL;
	}
	m->front_alloc_len = m->front.iov_len = front_len;

	dout("ceph_msg_new %p front %d\n", m, front_len);
	return m;

out2:
	ceph_msg_put(m);
out:
	if (!can_fail) {
		pr_err("msg_new can't create type %d front %d\n", type,
		       front_len);
		WARN_ON(1);
	} else {
		dout("msg_new can't create type %d front %d\n", type,
		     front_len);
	}
	return NULL;
}