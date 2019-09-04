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
struct policydb {int /*<<< orphan*/  policyvers; } ;
struct constraint_node {int permissions; struct constraint_expr* expr; struct constraint_node* next; } ;
struct constraint_expr {int expr_type; int attr; int op; int /*<<< orphan*/  type_names; int /*<<< orphan*/  names; struct constraint_expr* next; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
#define  CEXPR_NAMES 128 
 int /*<<< orphan*/  POLICYDB_VERSION_CONSTRAINT_NAMES ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int ebitmap_write (int /*<<< orphan*/ *,void*) ; 
 int put_entry (int /*<<< orphan*/ *,int,int,void*) ; 
 int type_set_write (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int write_cons_helper(struct policydb *p, struct constraint_node *node,
			     void *fp)
{
	struct constraint_node *c;
	struct constraint_expr *e;
	__le32 buf[3];
	u32 nel;
	int rc;

	for (c = node; c; c = c->next) {
		nel = 0;
		for (e = c->expr; e; e = e->next)
			nel++;
		buf[0] = cpu_to_le32(c->permissions);
		buf[1] = cpu_to_le32(nel);
		rc = put_entry(buf, sizeof(u32), 2, fp);
		if (rc)
			return rc;
		for (e = c->expr; e; e = e->next) {
			buf[0] = cpu_to_le32(e->expr_type);
			buf[1] = cpu_to_le32(e->attr);
			buf[2] = cpu_to_le32(e->op);
			rc = put_entry(buf, sizeof(u32), 3, fp);
			if (rc)
				return rc;

			switch (e->expr_type) {
			case CEXPR_NAMES:
				rc = ebitmap_write(&e->names, fp);
				if (rc)
					return rc;
				if (p->policyvers >=
					POLICYDB_VERSION_CONSTRAINT_NAMES) {
					rc = type_set_write(e->type_names, fp);
					if (rc)
						return rc;
				}
				break;
			default:
				break;
			}
		}
	}

	return 0;
}