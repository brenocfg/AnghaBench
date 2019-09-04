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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  table; } ;
struct policydb {scalar_t__ policyvers; TYPE_1__ p_commons; } ;
struct hashtab {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  table; void* nprim; } ;
struct class_datum {char* comkey; void* default_type; void* default_range; void* default_role; void* default_user; int /*<<< orphan*/  validatetrans; int /*<<< orphan*/  constraints; TYPE_2__ permissions; int /*<<< orphan*/  comdatum; void* value; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PERM_SYMTAB_SIZE ; 
 scalar_t__ POLICYDB_VERSION_DEFAULT_TYPE ; 
 scalar_t__ POLICYDB_VERSION_NEW_OBJECT_DEFAULTS ; 
 scalar_t__ POLICYDB_VERSION_VALIDATETRANS ; 
 int /*<<< orphan*/  cls_destroy (char*,struct class_datum*,int /*<<< orphan*/ *) ; 
 int hashtab_insert (struct hashtab*,char*,struct class_datum*) ; 
 int /*<<< orphan*/  hashtab_search (int /*<<< orphan*/ ,char*) ; 
 struct class_datum* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int next_entry (int /*<<< orphan*/ *,void*,int) ; 
 int perm_read (struct policydb*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int read_cons_helper (struct policydb*,int /*<<< orphan*/ *,int,int,void*) ; 
 int str_read (char**,int /*<<< orphan*/ ,void*,int) ; 
 int symtab_init (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int class_read(struct policydb *p, struct hashtab *h, void *fp)
{
	char *key = NULL;
	struct class_datum *cladatum;
	__le32 buf[6];
	u32 len, len2, ncons, nel;
	int i, rc;

	cladatum = kzalloc(sizeof(*cladatum), GFP_KERNEL);
	if (!cladatum)
		return -ENOMEM;

	rc = next_entry(buf, fp, sizeof(u32)*6);
	if (rc)
		goto bad;

	len = le32_to_cpu(buf[0]);
	len2 = le32_to_cpu(buf[1]);
	cladatum->value = le32_to_cpu(buf[2]);

	rc = symtab_init(&cladatum->permissions, PERM_SYMTAB_SIZE);
	if (rc)
		goto bad;
	cladatum->permissions.nprim = le32_to_cpu(buf[3]);
	nel = le32_to_cpu(buf[4]);

	ncons = le32_to_cpu(buf[5]);

	rc = str_read(&key, GFP_KERNEL, fp, len);
	if (rc)
		goto bad;

	if (len2) {
		rc = str_read(&cladatum->comkey, GFP_KERNEL, fp, len2);
		if (rc)
			goto bad;

		rc = -EINVAL;
		cladatum->comdatum = hashtab_search(p->p_commons.table, cladatum->comkey);
		if (!cladatum->comdatum) {
			pr_err("SELinux:  unknown common %s\n",
			       cladatum->comkey);
			goto bad;
		}
	}
	for (i = 0; i < nel; i++) {
		rc = perm_read(p, cladatum->permissions.table, fp);
		if (rc)
			goto bad;
	}

	rc = read_cons_helper(p, &cladatum->constraints, ncons, 0, fp);
	if (rc)
		goto bad;

	if (p->policyvers >= POLICYDB_VERSION_VALIDATETRANS) {
		/* grab the validatetrans rules */
		rc = next_entry(buf, fp, sizeof(u32));
		if (rc)
			goto bad;
		ncons = le32_to_cpu(buf[0]);
		rc = read_cons_helper(p, &cladatum->validatetrans,
				ncons, 1, fp);
		if (rc)
			goto bad;
	}

	if (p->policyvers >= POLICYDB_VERSION_NEW_OBJECT_DEFAULTS) {
		rc = next_entry(buf, fp, sizeof(u32) * 3);
		if (rc)
			goto bad;

		cladatum->default_user = le32_to_cpu(buf[0]);
		cladatum->default_role = le32_to_cpu(buf[1]);
		cladatum->default_range = le32_to_cpu(buf[2]);
	}

	if (p->policyvers >= POLICYDB_VERSION_DEFAULT_TYPE) {
		rc = next_entry(buf, fp, sizeof(u32) * 1);
		if (rc)
			goto bad;
		cladatum->default_type = le32_to_cpu(buf[0]);
	}

	rc = hashtab_insert(h, key, cladatum);
	if (rc)
		goto bad;

	return 0;
bad:
	cls_destroy(key, cladatum, NULL);
	return rc;
}