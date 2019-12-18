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
typedef  void* u32 ;
struct role_datum {scalar_t__ value; int /*<<< orphan*/  types; int /*<<< orphan*/  dominates; void* bounds; } ;
struct policydb {scalar_t__ policyvers; } ;
struct hashtab {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OBJECT_R ; 
 scalar_t__ OBJECT_R_VAL ; 
 scalar_t__ POLICYDB_VERSION_BOUNDARY ; 
 int ebitmap_read (int /*<<< orphan*/ *,void*) ; 
 int hashtab_insert (struct hashtab*,char*,struct role_datum*) ; 
 struct role_datum* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int next_entry (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  role_destroy (char*,struct role_datum*,int /*<<< orphan*/ *) ; 
 int str_read (char**,int /*<<< orphan*/ ,void*,void*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int role_read(struct policydb *p, struct hashtab *h, void *fp)
{
	char *key = NULL;
	struct role_datum *role;
	int rc, to_read = 2;
	__le32 buf[3];
	u32 len;

	role = kzalloc(sizeof(*role), GFP_KERNEL);
	if (!role)
		return -ENOMEM;

	if (p->policyvers >= POLICYDB_VERSION_BOUNDARY)
		to_read = 3;

	rc = next_entry(buf, fp, sizeof(buf[0]) * to_read);
	if (rc)
		goto bad;

	len = le32_to_cpu(buf[0]);
	role->value = le32_to_cpu(buf[1]);
	if (p->policyvers >= POLICYDB_VERSION_BOUNDARY)
		role->bounds = le32_to_cpu(buf[2]);

	rc = str_read(&key, GFP_KERNEL, fp, len);
	if (rc)
		goto bad;

	rc = ebitmap_read(&role->dominates, fp);
	if (rc)
		goto bad;

	rc = ebitmap_read(&role->types, fp);
	if (rc)
		goto bad;

	if (strcmp(key, OBJECT_R) == 0) {
		rc = -EINVAL;
		if (role->value != OBJECT_R_VAL) {
			pr_err("SELinux: Role %s has wrong value %d\n",
			       OBJECT_R, role->value);
			goto bad;
		}
		rc = 0;
		goto bad;
	}

	rc = hashtab_insert(h, key, role);
	if (rc)
		goto bad;
	return 0;
bad:
	role_destroy(key, role, NULL);
	return rc;
}