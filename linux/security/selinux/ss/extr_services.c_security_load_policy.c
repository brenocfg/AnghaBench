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
typedef  scalar_t__ u32 ;
struct sidtab_convert_params {struct sidtab* target; struct convert_context_args* args; int /*<<< orphan*/  func; } ;
struct sidtab {size_t len; scalar_t__ mls_enabled; } ;
struct selinux_state {int initialized; int /*<<< orphan*/  avc; TYPE_1__* ss; } ;
struct selinux_mapping {size_t len; scalar_t__ mls_enabled; } ;
struct selinux_map {struct sidtab* mapping; int /*<<< orphan*/  size; } ;
struct policydb {size_t len; scalar_t__ mls_enabled; } ;
struct policy_file {void* member_0; size_t member_1; } ;
struct convert_context_args {struct sidtab* newp; struct sidtab* oldp; struct selinux_state* state; } ;
struct TYPE_2__ {int /*<<< orphan*/  policy_rwlock; scalar_t__ latest_granting; struct selinux_map map; struct sidtab* sidtab; struct sidtab policydb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  avc_ss_reset (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  convert_context ; 
 struct sidtab* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sidtab*) ; 
 struct sidtab* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sidtab*,struct sidtab*,int) ; 
 int /*<<< orphan*/  policydb_destroy (struct sidtab*) ; 
 int policydb_load_isids (struct sidtab*,struct sidtab*) ; 
 int policydb_read (struct sidtab*,struct policy_file*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  secclass_map ; 
 int /*<<< orphan*/  security_load_policycaps (struct selinux_state*) ; 
 int security_preserve_bools (struct selinux_state*,struct sidtab*) ; 
 int /*<<< orphan*/  selinux_complete_init () ; 
 int /*<<< orphan*/  selinux_netlbl_cache_invalidate () ; 
 int selinux_set_mapping (struct sidtab*,int /*<<< orphan*/ ,struct selinux_map*) ; 
 int /*<<< orphan*/  selinux_status_update_policyload (struct selinux_state*,scalar_t__) ; 
 int /*<<< orphan*/  selinux_xfrm_notify_policyload () ; 
 int /*<<< orphan*/  selnl_notify_policyload (scalar_t__) ; 
 int sidtab_convert (struct sidtab*,struct sidtab_convert_params*) ; 
 int /*<<< orphan*/  sidtab_destroy (struct sidtab*) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

int security_load_policy(struct selinux_state *state, void *data, size_t len)
{
	struct policydb *policydb;
	struct sidtab *oldsidtab, *newsidtab;
	struct policydb *oldpolicydb, *newpolicydb;
	struct selinux_mapping *oldmapping;
	struct selinux_map newmap;
	struct sidtab_convert_params convert_params;
	struct convert_context_args args;
	u32 seqno;
	int rc = 0;
	struct policy_file file = { data, len }, *fp = &file;

	oldpolicydb = kcalloc(2, sizeof(*oldpolicydb), GFP_KERNEL);
	if (!oldpolicydb) {
		rc = -ENOMEM;
		goto out;
	}
	newpolicydb = oldpolicydb + 1;

	policydb = &state->ss->policydb;

	newsidtab = kmalloc(sizeof(*newsidtab), GFP_KERNEL);
	if (!newsidtab) {
		rc = -ENOMEM;
		goto out;
	}

	if (!state->initialized) {
		rc = policydb_read(policydb, fp);
		if (rc) {
			kfree(newsidtab);
			goto out;
		}

		policydb->len = len;
		rc = selinux_set_mapping(policydb, secclass_map,
					 &state->ss->map);
		if (rc) {
			kfree(newsidtab);
			policydb_destroy(policydb);
			goto out;
		}

		rc = policydb_load_isids(policydb, newsidtab);
		if (rc) {
			kfree(newsidtab);
			policydb_destroy(policydb);
			goto out;
		}

		state->ss->sidtab = newsidtab;
		security_load_policycaps(state);
		state->initialized = 1;
		seqno = ++state->ss->latest_granting;
		selinux_complete_init();
		avc_ss_reset(state->avc, seqno);
		selnl_notify_policyload(seqno);
		selinux_status_update_policyload(state, seqno);
		selinux_netlbl_cache_invalidate();
		selinux_xfrm_notify_policyload();
		goto out;
	}

	rc = policydb_read(newpolicydb, fp);
	if (rc) {
		kfree(newsidtab);
		goto out;
	}

	newpolicydb->len = len;
	/* If switching between different policy types, log MLS status */
	if (policydb->mls_enabled && !newpolicydb->mls_enabled)
		pr_info("SELinux: Disabling MLS support...\n");
	else if (!policydb->mls_enabled && newpolicydb->mls_enabled)
		pr_info("SELinux: Enabling MLS support...\n");

	rc = policydb_load_isids(newpolicydb, newsidtab);
	if (rc) {
		pr_err("SELinux:  unable to load the initial SIDs\n");
		policydb_destroy(newpolicydb);
		kfree(newsidtab);
		goto out;
	}

	rc = selinux_set_mapping(newpolicydb, secclass_map, &newmap);
	if (rc)
		goto err;

	rc = security_preserve_bools(state, newpolicydb);
	if (rc) {
		pr_err("SELinux:  unable to preserve booleans\n");
		goto err;
	}

	oldsidtab = state->ss->sidtab;

	/*
	 * Convert the internal representations of contexts
	 * in the new SID table.
	 */
	args.state = state;
	args.oldp = policydb;
	args.newp = newpolicydb;

	convert_params.func = convert_context;
	convert_params.args = &args;
	convert_params.target = newsidtab;

	rc = sidtab_convert(oldsidtab, &convert_params);
	if (rc) {
		pr_err("SELinux:  unable to convert the internal"
			" representation of contexts in the new SID"
			" table\n");
		goto err;
	}

	/* Save the old policydb and SID table to free later. */
	memcpy(oldpolicydb, policydb, sizeof(*policydb));

	/* Install the new policydb and SID table. */
	write_lock_irq(&state->ss->policy_rwlock);
	memcpy(policydb, newpolicydb, sizeof(*policydb));
	state->ss->sidtab = newsidtab;
	security_load_policycaps(state);
	oldmapping = state->ss->map.mapping;
	state->ss->map.mapping = newmap.mapping;
	state->ss->map.size = newmap.size;
	seqno = ++state->ss->latest_granting;
	write_unlock_irq(&state->ss->policy_rwlock);

	/* Free the old policydb and SID table. */
	policydb_destroy(oldpolicydb);
	sidtab_destroy(oldsidtab);
	kfree(oldsidtab);
	kfree(oldmapping);

	avc_ss_reset(state->avc, seqno);
	selnl_notify_policyload(seqno);
	selinux_status_update_policyload(state, seqno);
	selinux_netlbl_cache_invalidate();
	selinux_xfrm_notify_policyload();

	rc = 0;
	goto out;

err:
	kfree(newmap.mapping);
	sidtab_destroy(newsidtab);
	kfree(newsidtab);
	policydb_destroy(newpolicydb);

out:
	kfree(oldpolicydb);
	return rc;
}