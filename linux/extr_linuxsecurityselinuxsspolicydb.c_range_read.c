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
typedef  int u32 ;
struct range_trans {void* target_class; void* target_type; void* source_type; } ;
struct policydb {scalar_t__ policyvers; int /*<<< orphan*/  range_tr; void* process_class; } ;
struct mls_range {void* target_class; void* target_type; void* source_type; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ POLICYDB_VERSION_MLS ; 
 scalar_t__ POLICYDB_VERSION_RANGETRANS ; 
 int /*<<< orphan*/  hash_eval (int /*<<< orphan*/ ,char*) ; 
 int hashtab_insert (int /*<<< orphan*/ ,struct range_trans*,struct range_trans*) ; 
 int /*<<< orphan*/  kfree (struct range_trans*) ; 
 struct range_trans* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mls_range_isvalid (struct policydb*,struct range_trans*) ; 
 int mls_read_range_helper (struct range_trans*,void*) ; 
 int next_entry (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  policydb_class_isvalid (struct policydb*,void*) ; 
 int /*<<< orphan*/  policydb_type_isvalid (struct policydb*,void*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int range_read(struct policydb *p, void *fp)
{
	struct range_trans *rt = NULL;
	struct mls_range *r = NULL;
	int i, rc;
	__le32 buf[2];
	u32 nel;

	if (p->policyvers < POLICYDB_VERSION_MLS)
		return 0;

	rc = next_entry(buf, fp, sizeof(u32));
	if (rc)
		return rc;

	nel = le32_to_cpu(buf[0]);
	for (i = 0; i < nel; i++) {
		rc = -ENOMEM;
		rt = kzalloc(sizeof(*rt), GFP_KERNEL);
		if (!rt)
			goto out;

		rc = next_entry(buf, fp, (sizeof(u32) * 2));
		if (rc)
			goto out;

		rt->source_type = le32_to_cpu(buf[0]);
		rt->target_type = le32_to_cpu(buf[1]);
		if (p->policyvers >= POLICYDB_VERSION_RANGETRANS) {
			rc = next_entry(buf, fp, sizeof(u32));
			if (rc)
				goto out;
			rt->target_class = le32_to_cpu(buf[0]);
		} else
			rt->target_class = p->process_class;

		rc = -EINVAL;
		if (!policydb_type_isvalid(p, rt->source_type) ||
		    !policydb_type_isvalid(p, rt->target_type) ||
		    !policydb_class_isvalid(p, rt->target_class))
			goto out;

		rc = -ENOMEM;
		r = kzalloc(sizeof(*r), GFP_KERNEL);
		if (!r)
			goto out;

		rc = mls_read_range_helper(r, fp);
		if (rc)
			goto out;

		rc = -EINVAL;
		if (!mls_range_isvalid(p, r)) {
			pr_warn("SELinux:  rangetrans:  invalid range\n");
			goto out;
		}

		rc = hashtab_insert(p->range_tr, rt, r);
		if (rc)
			goto out;

		rt = NULL;
		r = NULL;
	}
	hash_eval(p->range_tr, "rangetr");
	rc = 0;
out:
	kfree(rt);
	kfree(r);
	return rc;
}