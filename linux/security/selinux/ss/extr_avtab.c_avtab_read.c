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
typedef  scalar_t__ u32 ;
struct policydb {int dummy; } ;
struct avtab {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int avtab_alloc (struct avtab*,scalar_t__) ; 
 int /*<<< orphan*/  avtab_destroy (struct avtab*) ; 
 int /*<<< orphan*/  avtab_insertf ; 
 int avtab_read_item (struct avtab*,void*,struct policydb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int next_entry (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int avtab_read(struct avtab *a, void *fp, struct policydb *pol)
{
	int rc;
	__le32 buf[1];
	u32 nel, i;


	rc = next_entry(buf, fp, sizeof(u32));
	if (rc < 0) {
		pr_err("SELinux: avtab: truncated table\n");
		goto bad;
	}
	nel = le32_to_cpu(buf[0]);
	if (!nel) {
		pr_err("SELinux: avtab: table is empty\n");
		rc = -EINVAL;
		goto bad;
	}

	rc = avtab_alloc(a, nel);
	if (rc)
		goto bad;

	for (i = 0; i < nel; i++) {
		rc = avtab_read_item(a, fp, pol, avtab_insertf, NULL);
		if (rc) {
			if (rc == -ENOMEM)
				pr_err("SELinux: avtab: out of memory\n");
			else if (rc == -EEXIST)
				pr_err("SELinux: avtab: duplicate entry\n");

			goto bad;
		}
	}

	rc = 0;
out:
	return rc;

bad:
	avtab_destroy(a);
	goto out;
}