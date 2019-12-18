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
struct policydb {scalar_t__ policyvers; } ;
struct context {int /*<<< orphan*/  range; void* type; void* role; void* user; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ POLICYDB_VERSION_MLS ; 
 int /*<<< orphan*/  context_destroy (struct context*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int mls_read_range_helper (int /*<<< orphan*/ *,void*) ; 
 int next_entry (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  policydb_context_isvalid (struct policydb*,struct context*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int context_read_and_validate(struct context *c,
				     struct policydb *p,
				     void *fp)
{
	__le32 buf[3];
	int rc;

	rc = next_entry(buf, fp, sizeof buf);
	if (rc) {
		pr_err("SELinux: context truncated\n");
		goto out;
	}
	c->user = le32_to_cpu(buf[0]);
	c->role = le32_to_cpu(buf[1]);
	c->type = le32_to_cpu(buf[2]);
	if (p->policyvers >= POLICYDB_VERSION_MLS) {
		rc = mls_read_range_helper(&c->range, fp);
		if (rc) {
			pr_err("SELinux: error reading MLS range of context\n");
			goto out;
		}
	}

	rc = -EINVAL;
	if (!policydb_context_isvalid(p, c)) {
		pr_err("SELinux:  invalid security context\n");
		context_destroy(c);
		goto out;
	}
	rc = 0;
out:
	return rc;
}