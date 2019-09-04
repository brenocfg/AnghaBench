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
struct policydb {int dummy; } ;
struct perm_datum {void* value; } ;
struct hashtab {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int hashtab_insert (struct hashtab*,char*,struct perm_datum*) ; 
 struct perm_datum* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int next_entry (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  perm_destroy (char*,struct perm_datum*,int /*<<< orphan*/ *) ; 
 int str_read (char**,int /*<<< orphan*/ ,void*,void*) ; 

__attribute__((used)) static int perm_read(struct policydb *p, struct hashtab *h, void *fp)
{
	char *key = NULL;
	struct perm_datum *perdatum;
	int rc;
	__le32 buf[2];
	u32 len;

	perdatum = kzalloc(sizeof(*perdatum), GFP_KERNEL);
	if (!perdatum)
		return -ENOMEM;

	rc = next_entry(buf, fp, sizeof buf);
	if (rc)
		goto bad;

	len = le32_to_cpu(buf[0]);
	perdatum->value = le32_to_cpu(buf[1]);

	rc = str_read(&key, GFP_KERNEL, fp, len);
	if (rc)
		goto bad;

	rc = hashtab_insert(h, key, perdatum);
	if (rc)
		goto bad;

	return 0;
bad:
	perm_destroy(key, perdatum, NULL);
	return rc;
}