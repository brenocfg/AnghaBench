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
typedef  int /*<<< orphan*/  u32 ;
struct role_trans {size_t role; size_t type; size_t new_role; size_t tclass; struct role_trans* next; } ;
struct policydb {scalar_t__ policyvers; struct role_trans* role_tr; } ;

/* Variables and functions */
 scalar_t__ POLICYDB_VERSION_ROLETRANS ; 
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 
 int put_entry (int /*<<< orphan*/ *,int,int,void*) ; 

__attribute__((used)) static int role_trans_write(struct policydb *p, void *fp)
{
	struct role_trans *r = p->role_tr;
	struct role_trans *tr;
	u32 buf[3];
	size_t nel;
	int rc;

	nel = 0;
	for (tr = r; tr; tr = tr->next)
		nel++;
	buf[0] = cpu_to_le32(nel);
	rc = put_entry(buf, sizeof(u32), 1, fp);
	if (rc)
		return rc;
	for (tr = r; tr; tr = tr->next) {
		buf[0] = cpu_to_le32(tr->role);
		buf[1] = cpu_to_le32(tr->type);
		buf[2] = cpu_to_le32(tr->new_role);
		rc = put_entry(buf, sizeof(u32), 3, fp);
		if (rc)
			return rc;
		if (p->policyvers >= POLICYDB_VERSION_ROLETRANS) {
			buf[0] = cpu_to_le32(tr->tclass);
			rc = put_entry(buf, sizeof(u32), 1, fp);
			if (rc)
				return rc;
		}
	}

	return 0;
}