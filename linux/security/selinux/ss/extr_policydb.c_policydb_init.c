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
struct policydb {TYPE_1__* symtab; void* range_tr; void* filename_trans; int /*<<< orphan*/  permissive_map; int /*<<< orphan*/  policycaps; int /*<<< orphan*/  filename_trans_ttypes; int /*<<< orphan*/  te_avtab; } ;
struct TYPE_2__ {void* table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int SYM_NUM ; 
 int avtab_init (int /*<<< orphan*/ *) ; 
 int cond_policydb_init (struct policydb*) ; 
 int /*<<< orphan*/ * destroy_f ; 
 int /*<<< orphan*/  ebitmap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filenametr_cmp ; 
 int /*<<< orphan*/  filenametr_hash ; 
 void* hashtab_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hashtab_destroy (void*) ; 
 int /*<<< orphan*/  hashtab_map (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct policydb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rangetr_cmp ; 
 int /*<<< orphan*/  rangetr_hash ; 
 int roles_init (struct policydb*) ; 
 int symtab_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * symtab_sizes ; 

__attribute__((used)) static int policydb_init(struct policydb *p)
{
	int i, rc;

	memset(p, 0, sizeof(*p));

	for (i = 0; i < SYM_NUM; i++) {
		rc = symtab_init(&p->symtab[i], symtab_sizes[i]);
		if (rc)
			goto out;
	}

	rc = avtab_init(&p->te_avtab);
	if (rc)
		goto out;

	rc = roles_init(p);
	if (rc)
		goto out;

	rc = cond_policydb_init(p);
	if (rc)
		goto out;

	p->filename_trans = hashtab_create(filenametr_hash, filenametr_cmp,
					   (1 << 10));
	if (!p->filename_trans) {
		rc = -ENOMEM;
		goto out;
	}

	p->range_tr = hashtab_create(rangetr_hash, rangetr_cmp, 256);
	if (!p->range_tr) {
		rc = -ENOMEM;
		goto out;
	}

	ebitmap_init(&p->filename_trans_ttypes);
	ebitmap_init(&p->policycaps);
	ebitmap_init(&p->permissive_map);

	return 0;
out:
	hashtab_destroy(p->filename_trans);
	hashtab_destroy(p->range_tr);
	for (i = 0; i < SYM_NUM; i++) {
		hashtab_map(p->symtab[i].table, destroy_f[i], NULL);
		hashtab_destroy(p->symtab[i].table);
	}
	return rc;
}