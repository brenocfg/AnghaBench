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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  in_addr; } ;
struct ceph_fsid {TYPE_1__ addr; } ;
struct ceph_monmap {int epoch; int num_mon; struct ceph_fsid* mon_inst; struct ceph_fsid fsid; } ;
typedef  int /*<<< orphan*/  fsid ;

/* Variables and functions */
 int CEPH_MAX_MON ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct ceph_monmap* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  bad ; 
 int ceph_decode_32 (void**) ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_addr (TYPE_1__*) ; 
 int /*<<< orphan*/  ceph_decode_copy (void**,struct ceph_fsid*,int) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_pr_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dout (char*,int,...) ; 
 int /*<<< orphan*/  kfree (struct ceph_monmap*) ; 
 struct ceph_monmap* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mon_inst ; 
 int /*<<< orphan*/  struct_size (struct ceph_monmap*,int /*<<< orphan*/ ,int) ; 

struct ceph_monmap *ceph_monmap_decode(void *p, void *end)
{
	struct ceph_monmap *m = NULL;
	int i, err = -EINVAL;
	struct ceph_fsid fsid;
	u32 epoch, num_mon;
	u32 len;

	ceph_decode_32_safe(&p, end, len, bad);
	ceph_decode_need(&p, end, len, bad);

	dout("monmap_decode %p %p len %d\n", p, end, (int)(end-p));
	p += sizeof(u16);  /* skip version */

	ceph_decode_need(&p, end, sizeof(fsid) + 2*sizeof(u32), bad);
	ceph_decode_copy(&p, &fsid, sizeof(fsid));
	epoch = ceph_decode_32(&p);

	num_mon = ceph_decode_32(&p);
	ceph_decode_need(&p, end, num_mon*sizeof(m->mon_inst[0]), bad);

	if (num_mon > CEPH_MAX_MON)
		goto bad;
	m = kmalloc(struct_size(m, mon_inst, num_mon), GFP_NOFS);
	if (m == NULL)
		return ERR_PTR(-ENOMEM);
	m->fsid = fsid;
	m->epoch = epoch;
	m->num_mon = num_mon;
	ceph_decode_copy(&p, m->mon_inst, num_mon*sizeof(m->mon_inst[0]));
	for (i = 0; i < num_mon; i++)
		ceph_decode_addr(&m->mon_inst[i].addr);

	dout("monmap_decode epoch %d, num_mon %d\n", m->epoch,
	     m->num_mon);
	for (i = 0; i < m->num_mon; i++)
		dout("monmap_decode  mon%d is %s\n", i,
		     ceph_pr_addr(&m->mon_inst[i].addr.in_addr));
	return m;

bad:
	dout("monmap_decode failed with %d\n", err);
	kfree(m);
	return ERR_PTR(err);
}