#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct policydb_compat_info {size_t sym_num; size_t ocon_num; } ;
struct TYPE_5__ {unsigned int nprim; } ;
struct ebitmap {int dummy; } ;
struct policydb {size_t policyvers; struct ebitmap* type_attr_map_array; TYPE_2__ p_types; int /*<<< orphan*/  role_allow; int /*<<< orphan*/  cond_list; int /*<<< orphan*/  te_avtab; TYPE_1__* symtab; struct ebitmap permissive_map; struct ebitmap policycaps; scalar_t__ allow_unknown; scalar_t__ reject_unknown; scalar_t__ mls_enabled; } ;
struct policy_data {struct policydb* p; void* fp; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {size_t nel; } ;
struct TYPE_4__ {size_t nprim; TYPE_3__* table; } ;

/* Variables and functions */
 size_t ALLOW_UNKNOWN ; 
 int EINVAL ; 
 size_t POLICYDB_CONFIG_MLS ; 
 size_t POLICYDB_MAGIC ; 
 int /*<<< orphan*/ * POLICYDB_STRING ; 
 size_t POLICYDB_VERSION_AVTAB ; 
 size_t POLICYDB_VERSION_PERMISSIVE ; 
 size_t POLICYDB_VERSION_POLCAP ; 
 size_t REJECT_UNKNOWN ; 
 int avtab_write (struct policydb*,int /*<<< orphan*/ *,void*) ; 
 int cond_write_list (struct policydb*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 
 int ebitmap_write (struct ebitmap*,void*) ; 
 int filename_trans_write (struct policydb*,void*) ; 
 int genfs_write (struct policydb*,void*) ; 
 int hashtab_map (TYPE_3__*,int /*<<< orphan*/ ,struct policy_data*) ; 
 int ocontext_write (struct policydb*,struct policydb_compat_info*,void*) ; 
 struct policydb_compat_info* policydb_lookup_compat (size_t) ; 
 int /*<<< orphan*/  pr_err (char*,size_t,...) ; 
 int put_entry (int /*<<< orphan*/ *,int,int,void*) ; 
 int range_write (struct policydb*,void*) ; 
 int role_allow_write (int /*<<< orphan*/ ,void*) ; 
 int role_trans_write (struct policydb*,void*) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * write_f ; 

int policydb_write(struct policydb *p, void *fp)
{
	unsigned int i, num_syms;
	int rc;
	__le32 buf[4];
	u32 config;
	size_t len;
	struct policydb_compat_info *info;

	/*
	 * refuse to write policy older than compressed avtab
	 * to simplify the writer.  There are other tests dropped
	 * since we assume this throughout the writer code.  Be
	 * careful if you ever try to remove this restriction
	 */
	if (p->policyvers < POLICYDB_VERSION_AVTAB) {
		pr_err("SELinux: refusing to write policy version %d."
		       "  Because it is less than version %d\n", p->policyvers,
		       POLICYDB_VERSION_AVTAB);
		return -EINVAL;
	}

	config = 0;
	if (p->mls_enabled)
		config |= POLICYDB_CONFIG_MLS;

	if (p->reject_unknown)
		config |= REJECT_UNKNOWN;
	if (p->allow_unknown)
		config |= ALLOW_UNKNOWN;

	/* Write the magic number and string identifiers. */
	buf[0] = cpu_to_le32(POLICYDB_MAGIC);
	len = strlen(POLICYDB_STRING);
	buf[1] = cpu_to_le32(len);
	rc = put_entry(buf, sizeof(u32), 2, fp);
	if (rc)
		return rc;
	rc = put_entry(POLICYDB_STRING, 1, len, fp);
	if (rc)
		return rc;

	/* Write the version, config, and table sizes. */
	info = policydb_lookup_compat(p->policyvers);
	if (!info) {
		pr_err("SELinux: compatibility lookup failed for policy "
		    "version %d", p->policyvers);
		return -EINVAL;
	}

	buf[0] = cpu_to_le32(p->policyvers);
	buf[1] = cpu_to_le32(config);
	buf[2] = cpu_to_le32(info->sym_num);
	buf[3] = cpu_to_le32(info->ocon_num);

	rc = put_entry(buf, sizeof(u32), 4, fp);
	if (rc)
		return rc;

	if (p->policyvers >= POLICYDB_VERSION_POLCAP) {
		rc = ebitmap_write(&p->policycaps, fp);
		if (rc)
			return rc;
	}

	if (p->policyvers >= POLICYDB_VERSION_PERMISSIVE) {
		rc = ebitmap_write(&p->permissive_map, fp);
		if (rc)
			return rc;
	}

	num_syms = info->sym_num;
	for (i = 0; i < num_syms; i++) {
		struct policy_data pd;

		pd.fp = fp;
		pd.p = p;

		buf[0] = cpu_to_le32(p->symtab[i].nprim);
		buf[1] = cpu_to_le32(p->symtab[i].table->nel);

		rc = put_entry(buf, sizeof(u32), 2, fp);
		if (rc)
			return rc;
		rc = hashtab_map(p->symtab[i].table, write_f[i], &pd);
		if (rc)
			return rc;
	}

	rc = avtab_write(p, &p->te_avtab, fp);
	if (rc)
		return rc;

	rc = cond_write_list(p, p->cond_list, fp);
	if (rc)
		return rc;

	rc = role_trans_write(p, fp);
	if (rc)
		return rc;

	rc = role_allow_write(p->role_allow, fp);
	if (rc)
		return rc;

	rc = filename_trans_write(p, fp);
	if (rc)
		return rc;

	rc = ocontext_write(p, info, fp);
	if (rc)
		return rc;

	rc = genfs_write(p, fp);
	if (rc)
		return rc;

	rc = range_write(p, fp);
	if (rc)
		return rc;

	for (i = 0; i < p->p_types.nprim; i++) {
		struct ebitmap *e = &p->type_attr_map_array[i];

		rc = ebitmap_write(e, fp);
		if (rc)
			return rc;
	}

	return 0;
}