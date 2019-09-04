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
typedef  int /*<<< orphan*/  u32 ;
struct policydb {struct genfs* genfs; } ;
struct TYPE_4__ {size_t sclass; } ;
struct TYPE_3__ {int /*<<< orphan*/ * name; } ;
struct ocontext {int /*<<< orphan*/ * context; TYPE_2__ v; TYPE_1__ u; struct ocontext* next; } ;
struct genfs {struct ocontext* head; int /*<<< orphan*/ * fstype; struct genfs* next; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int context_write (struct policydb*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 
 int put_entry (int /*<<< orphan*/ *,int,int,void*) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int genfs_write(struct policydb *p, void *fp)
{
	struct genfs *genfs;
	struct ocontext *c;
	size_t len;
	__le32 buf[1];
	int rc;

	len = 0;
	for (genfs = p->genfs; genfs; genfs = genfs->next)
		len++;
	buf[0] = cpu_to_le32(len);
	rc = put_entry(buf, sizeof(u32), 1, fp);
	if (rc)
		return rc;
	for (genfs = p->genfs; genfs; genfs = genfs->next) {
		len = strlen(genfs->fstype);
		buf[0] = cpu_to_le32(len);
		rc = put_entry(buf, sizeof(u32), 1, fp);
		if (rc)
			return rc;
		rc = put_entry(genfs->fstype, 1, len, fp);
		if (rc)
			return rc;
		len = 0;
		for (c = genfs->head; c; c = c->next)
			len++;
		buf[0] = cpu_to_le32(len);
		rc = put_entry(buf, sizeof(u32), 1, fp);
		if (rc)
			return rc;
		for (c = genfs->head; c; c = c->next) {
			len = strlen(c->u.name);
			buf[0] = cpu_to_le32(len);
			rc = put_entry(buf, sizeof(u32), 1, fp);
			if (rc)
				return rc;
			rc = put_entry(c->u.name, 1, len, fp);
			if (rc)
				return rc;
			buf[0] = cpu_to_le32(c->v.sclass);
			rc = put_entry(buf, sizeof(u32), 1, fp);
			if (rc)
				return rc;
			rc = context_write(p, &c->context[0], fp);
			if (rc)
				return rc;
		}
	}
	return 0;
}