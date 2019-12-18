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
struct role_trans {struct role_trans* next; struct ocontext* head; struct role_trans* fstype; } ;
struct role_allow {struct role_allow* next; struct ocontext* head; struct role_allow* fstype; } ;
struct TYPE_4__ {int nprim; } ;
struct policydb {int /*<<< orphan*/  permissive_map; int /*<<< orphan*/  policycaps; int /*<<< orphan*/  filename_trans_ttypes; int /*<<< orphan*/ * type_attr_map_array; TYPE_2__ p_types; int /*<<< orphan*/  range_tr; int /*<<< orphan*/  filename_trans; struct role_trans* role_allow; struct role_trans* role_tr; struct role_trans* genfs; struct ocontext** ocontexts; int /*<<< orphan*/  te_avtab; int /*<<< orphan*/ * type_val_to_struct; struct role_trans* user_val_to_struct; struct role_trans* role_val_to_struct; struct role_trans* class_val_to_struct; int /*<<< orphan*/ ** sym_val_to_name; TYPE_1__* symtab; } ;
struct ocontext {struct ocontext* next; } ;
struct genfs {struct genfs* next; struct ocontext* head; struct genfs* fstype; } ;
struct TYPE_3__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int OCON_FSUSE ; 
 int OCON_NUM ; 
 int SYM_NUM ; 
 int /*<<< orphan*/  avtab_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_policydb_destroy (struct policydb*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/ * destroy_f ; 
 int /*<<< orphan*/  ebitmap_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filenametr_destroy ; 
 int /*<<< orphan*/  hashtab_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashtab_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct role_trans*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocontext_destroy (struct ocontext*,int) ; 
 int /*<<< orphan*/  range_tr_destroy ; 

void policydb_destroy(struct policydb *p)
{
	struct ocontext *c, *ctmp;
	struct genfs *g, *gtmp;
	int i;
	struct role_allow *ra, *lra = NULL;
	struct role_trans *tr, *ltr = NULL;

	for (i = 0; i < SYM_NUM; i++) {
		cond_resched();
		hashtab_map(p->symtab[i].table, destroy_f[i], NULL);
		hashtab_destroy(p->symtab[i].table);
	}

	for (i = 0; i < SYM_NUM; i++)
		kvfree(p->sym_val_to_name[i]);

	kfree(p->class_val_to_struct);
	kfree(p->role_val_to_struct);
	kfree(p->user_val_to_struct);
	kvfree(p->type_val_to_struct);

	avtab_destroy(&p->te_avtab);

	for (i = 0; i < OCON_NUM; i++) {
		cond_resched();
		c = p->ocontexts[i];
		while (c) {
			ctmp = c;
			c = c->next;
			ocontext_destroy(ctmp, i);
		}
		p->ocontexts[i] = NULL;
	}

	g = p->genfs;
	while (g) {
		cond_resched();
		kfree(g->fstype);
		c = g->head;
		while (c) {
			ctmp = c;
			c = c->next;
			ocontext_destroy(ctmp, OCON_FSUSE);
		}
		gtmp = g;
		g = g->next;
		kfree(gtmp);
	}
	p->genfs = NULL;

	cond_policydb_destroy(p);

	for (tr = p->role_tr; tr; tr = tr->next) {
		cond_resched();
		kfree(ltr);
		ltr = tr;
	}
	kfree(ltr);

	for (ra = p->role_allow; ra; ra = ra->next) {
		cond_resched();
		kfree(lra);
		lra = ra;
	}
	kfree(lra);

	hashtab_map(p->filename_trans, filenametr_destroy, NULL);
	hashtab_destroy(p->filename_trans);

	hashtab_map(p->range_tr, range_tr_destroy, NULL);
	hashtab_destroy(p->range_tr);

	if (p->type_attr_map_array) {
		for (i = 0; i < p->p_types.nprim; i++)
			ebitmap_destroy(&p->type_attr_map_array[i]);
		kvfree(p->type_attr_map_array);
	}

	ebitmap_destroy(&p->filename_trans_ttypes);
	ebitmap_destroy(&p->policycaps);
	ebitmap_destroy(&p->permissive_map);
}