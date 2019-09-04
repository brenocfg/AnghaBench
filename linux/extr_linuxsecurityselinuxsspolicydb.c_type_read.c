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
struct type_datum {int primary; int attribute; void* bounds; void* value; } ;
struct policydb {scalar_t__ policyvers; } ;
struct hashtab {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ POLICYDB_VERSION_BOUNDARY ; 
 int TYPEDATUM_PROPERTY_ATTRIBUTE ; 
 int TYPEDATUM_PROPERTY_PRIMARY ; 
 int hashtab_insert (struct hashtab*,char*,struct type_datum*) ; 
 struct type_datum* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int next_entry (int /*<<< orphan*/ *,void*,int) ; 
 int str_read (char**,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  type_destroy (char*,struct type_datum*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int type_read(struct policydb *p, struct hashtab *h, void *fp)
{
	char *key = NULL;
	struct type_datum *typdatum;
	int rc, to_read = 3;
	__le32 buf[4];
	u32 len;

	typdatum = kzalloc(sizeof(*typdatum), GFP_KERNEL);
	if (!typdatum)
		return -ENOMEM;

	if (p->policyvers >= POLICYDB_VERSION_BOUNDARY)
		to_read = 4;

	rc = next_entry(buf, fp, sizeof(buf[0]) * to_read);
	if (rc)
		goto bad;

	len = le32_to_cpu(buf[0]);
	typdatum->value = le32_to_cpu(buf[1]);
	if (p->policyvers >= POLICYDB_VERSION_BOUNDARY) {
		u32 prop = le32_to_cpu(buf[2]);

		if (prop & TYPEDATUM_PROPERTY_PRIMARY)
			typdatum->primary = 1;
		if (prop & TYPEDATUM_PROPERTY_ATTRIBUTE)
			typdatum->attribute = 1;

		typdatum->bounds = le32_to_cpu(buf[3]);
	} else {
		typdatum->primary = le32_to_cpu(buf[2]);
	}

	rc = str_read(&key, GFP_KERNEL, fp, len);
	if (rc)
		goto bad;

	rc = hashtab_insert(h, key, typdatum);
	if (rc)
		goto bad;
	return 0;
bad:
	type_destroy(key, typdatum, NULL);
	return rc;
}