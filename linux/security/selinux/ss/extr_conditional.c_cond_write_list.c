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
struct cond_node {struct cond_node* next; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int cond_write_node (struct policydb*,struct cond_node*,void*) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int put_entry (int /*<<< orphan*/ *,int,int,void*) ; 

int cond_write_list(struct policydb *p, struct cond_node *list, void *fp)
{
	struct cond_node *cur;
	u32 len;
	__le32 buf[1];
	int rc;

	len = 0;
	for (cur = list; cur != NULL; cur = cur->next)
		len++;
	buf[0] = cpu_to_le32(len);
	rc = put_entry(buf, sizeof(u32), 1, fp);
	if (rc)
		return rc;

	for (cur = list; cur != NULL; cur = cur->next) {
		rc = cond_write_node(p, cur, fp);
		if (rc)
			return rc;
	}

	return 0;
}