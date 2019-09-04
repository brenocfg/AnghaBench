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
struct policydb {int dummy; } ;
struct hashtab {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  table; void* nprim; } ;
struct common_datum {TYPE_1__ permissions; void* value; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PERM_SYMTAB_SIZE ; 
 int /*<<< orphan*/  common_destroy (char*,struct common_datum*,int /*<<< orphan*/ *) ; 
 int hashtab_insert (struct hashtab*,char*,struct common_datum*) ; 
 struct common_datum* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int next_entry (int /*<<< orphan*/ *,void*,int) ; 
 int perm_read (struct policydb*,int /*<<< orphan*/ ,void*) ; 
 int str_read (char**,int /*<<< orphan*/ ,void*,int) ; 
 int symtab_init (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int common_read(struct policydb *p, struct hashtab *h, void *fp)
{
	char *key = NULL;
	struct common_datum *comdatum;
	__le32 buf[4];
	u32 len, nel;
	int i, rc;

	comdatum = kzalloc(sizeof(*comdatum), GFP_KERNEL);
	if (!comdatum)
		return -ENOMEM;

	rc = next_entry(buf, fp, sizeof buf);
	if (rc)
		goto bad;

	len = le32_to_cpu(buf[0]);
	comdatum->value = le32_to_cpu(buf[1]);

	rc = symtab_init(&comdatum->permissions, PERM_SYMTAB_SIZE);
	if (rc)
		goto bad;
	comdatum->permissions.nprim = le32_to_cpu(buf[2]);
	nel = le32_to_cpu(buf[3]);

	rc = str_read(&key, GFP_KERNEL, fp, len);
	if (rc)
		goto bad;

	for (i = 0; i < nel; i++) {
		rc = perm_read(p, comdatum->permissions.table, fp);
		if (rc)
			goto bad;
	}

	rc = hashtab_insert(h, key, comdatum);
	if (rc)
		goto bad;
	return 0;
bad:
	common_destroy(key, comdatum, NULL);
	return rc;
}