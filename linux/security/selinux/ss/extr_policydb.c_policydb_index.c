#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  nprim; } ;
struct TYPE_15__ {int /*<<< orphan*/  nprim; } ;
struct TYPE_14__ {int /*<<< orphan*/  nprim; } ;
struct TYPE_13__ {int /*<<< orphan*/  nprim; } ;
struct TYPE_18__ {int /*<<< orphan*/  nel; } ;
struct TYPE_12__ {int /*<<< orphan*/  nprim; } ;
struct TYPE_11__ {int /*<<< orphan*/  nprim; } ;
struct TYPE_10__ {int /*<<< orphan*/  nprim; } ;
struct policydb {TYPE_8__* symtab; void** sym_val_to_name; void* type_val_to_struct; TYPE_7__ p_types; void* user_val_to_struct; TYPE_6__ p_users; void* role_val_to_struct; TYPE_5__ p_roles; void* class_val_to_struct; TYPE_4__ p_classes; TYPE_9__ te_avtab; TYPE_3__ p_bools; TYPE_2__ p_cats; TYPE_1__ p_levels; scalar_t__ mls_enabled; } ;
struct TYPE_17__ {int /*<<< orphan*/  table; int /*<<< orphan*/  nprim; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SYM_NUM ; 
 int /*<<< orphan*/  avtab_hash_eval (TYPE_9__*,char*) ; 
 int cond_init_bool_indexes (struct policydb*) ; 
 int hashtab_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct policydb*) ; 
 int /*<<< orphan*/ * index_f ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* kvcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  symtab_hash_eval (TYPE_8__*) ; 

__attribute__((used)) static int policydb_index(struct policydb *p)
{
	int i, rc;

	if (p->mls_enabled)
		pr_debug("SELinux:  %d users, %d roles, %d types, %d bools, %d sens, %d cats\n",
			 p->p_users.nprim, p->p_roles.nprim, p->p_types.nprim,
			 p->p_bools.nprim, p->p_levels.nprim, p->p_cats.nprim);
	else
		pr_debug("SELinux:  %d users, %d roles, %d types, %d bools\n",
			 p->p_users.nprim, p->p_roles.nprim, p->p_types.nprim,
			 p->p_bools.nprim);

	pr_debug("SELinux:  %d classes, %d rules\n",
		 p->p_classes.nprim, p->te_avtab.nel);

#ifdef DEBUG_HASHES
	avtab_hash_eval(&p->te_avtab, "rules");
	symtab_hash_eval(p->symtab);
#endif

	p->class_val_to_struct = kcalloc(p->p_classes.nprim,
					 sizeof(*p->class_val_to_struct),
					 GFP_KERNEL);
	if (!p->class_val_to_struct)
		return -ENOMEM;

	p->role_val_to_struct = kcalloc(p->p_roles.nprim,
					sizeof(*p->role_val_to_struct),
					GFP_KERNEL);
	if (!p->role_val_to_struct)
		return -ENOMEM;

	p->user_val_to_struct = kcalloc(p->p_users.nprim,
					sizeof(*p->user_val_to_struct),
					GFP_KERNEL);
	if (!p->user_val_to_struct)
		return -ENOMEM;

	p->type_val_to_struct = kvcalloc(p->p_types.nprim,
					 sizeof(*p->type_val_to_struct),
					 GFP_KERNEL);
	if (!p->type_val_to_struct)
		return -ENOMEM;

	rc = cond_init_bool_indexes(p);
	if (rc)
		goto out;

	for (i = 0; i < SYM_NUM; i++) {
		p->sym_val_to_name[i] = kvcalloc(p->symtab[i].nprim,
						 sizeof(char *),
						 GFP_KERNEL);
		if (!p->sym_val_to_name[i])
			return -ENOMEM;

		rc = hashtab_map(p->symtab[i].table, index_f[i], p);
		if (rc)
			goto out;
	}
	rc = 0;
out:
	return rc;
}