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
struct constraint_node {struct constraint_expr* expr; void* permissions; struct constraint_node* next; } ;
struct constraint_expr {int expr_type; int attr; void* type_names; int /*<<< orphan*/  names; void* op; struct constraint_expr* next; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
#define  CEXPR_AND 132 
#define  CEXPR_ATTR 131 
 int /*<<< orphan*/  CEXPR_MAXDEPTH ; 
#define  CEXPR_NAMES 130 
#define  CEXPR_NOT 129 
#define  CEXPR_OR 128 
 int CEXPR_XTARGET ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  POLICYDB_VERSION_CONSTRAINT_NAMES ; 
 int ebitmap_read (int /*<<< orphan*/ *,void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int next_entry (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  type_set_init (void*) ; 
 int type_set_read (void*,void*) ; 

__attribute__((used)) static int read_cons_helper(struct policydb *p,
				struct constraint_node **nodep,
				int ncons, int allowxtarget, void *fp)
{
	struct constraint_node *c, *lc;
	struct constraint_expr *e, *le;
	__le32 buf[3];
	u32 nexpr;
	int rc, i, j, depth;

	lc = NULL;
	for (i = 0; i < ncons; i++) {
		c = kzalloc(sizeof(*c), GFP_KERNEL);
		if (!c)
			return -ENOMEM;

		if (lc)
			lc->next = c;
		else
			*nodep = c;

		rc = next_entry(buf, fp, (sizeof(u32) * 2));
		if (rc)
			return rc;
		c->permissions = le32_to_cpu(buf[0]);
		nexpr = le32_to_cpu(buf[1]);
		le = NULL;
		depth = -1;
		for (j = 0; j < nexpr; j++) {
			e = kzalloc(sizeof(*e), GFP_KERNEL);
			if (!e)
				return -ENOMEM;

			if (le)
				le->next = e;
			else
				c->expr = e;

			rc = next_entry(buf, fp, (sizeof(u32) * 3));
			if (rc)
				return rc;
			e->expr_type = le32_to_cpu(buf[0]);
			e->attr = le32_to_cpu(buf[1]);
			e->op = le32_to_cpu(buf[2]);

			switch (e->expr_type) {
			case CEXPR_NOT:
				if (depth < 0)
					return -EINVAL;
				break;
			case CEXPR_AND:
			case CEXPR_OR:
				if (depth < 1)
					return -EINVAL;
				depth--;
				break;
			case CEXPR_ATTR:
				if (depth == (CEXPR_MAXDEPTH - 1))
					return -EINVAL;
				depth++;
				break;
			case CEXPR_NAMES:
				if (!allowxtarget && (e->attr & CEXPR_XTARGET))
					return -EINVAL;
				if (depth == (CEXPR_MAXDEPTH - 1))
					return -EINVAL;
				depth++;
				rc = ebitmap_read(&e->names, fp);
				if (rc)
					return rc;
				if (p->policyvers >=
					POLICYDB_VERSION_CONSTRAINT_NAMES) {
						e->type_names = kzalloc(sizeof
						(*e->type_names),
						GFP_KERNEL);
					if (!e->type_names)
						return -ENOMEM;
					type_set_init(e->type_names);
					rc = type_set_read(e->type_names, fp);
					if (rc)
						return rc;
				}
				break;
			default:
				return -EINVAL;
			}
			le = e;
		}
		if (depth != 0)
			return -EINVAL;
		lc = c;
	}

	return 0;
}