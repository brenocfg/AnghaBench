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
struct hashtab {int dummy; } ;
struct cat_datum {void* isalias; void* value; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  cat_destroy (char*,struct cat_datum*,int /*<<< orphan*/ *) ; 
 int hashtab_insert (struct hashtab*,char*,struct cat_datum*) ; 
 struct cat_datum* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int next_entry (int /*<<< orphan*/ *,void*,int) ; 
 int str_read (char**,int /*<<< orphan*/ ,void*,void*) ; 

__attribute__((used)) static int cat_read(struct policydb *p, struct hashtab *h, void *fp)
{
	char *key = NULL;
	struct cat_datum *catdatum;
	int rc;
	__le32 buf[3];
	u32 len;

	catdatum = kzalloc(sizeof(*catdatum), GFP_ATOMIC);
	if (!catdatum)
		return -ENOMEM;

	rc = next_entry(buf, fp, sizeof buf);
	if (rc)
		goto bad;

	len = le32_to_cpu(buf[0]);
	catdatum->value = le32_to_cpu(buf[1]);
	catdatum->isalias = le32_to_cpu(buf[2]);

	rc = str_read(&key, GFP_ATOMIC, fp, len);
	if (rc)
		goto bad;

	rc = hashtab_insert(h, key, catdatum);
	if (rc)
		goto bad;
	return 0;
bad:
	cat_destroy(key, catdatum, NULL);
	return rc;
}