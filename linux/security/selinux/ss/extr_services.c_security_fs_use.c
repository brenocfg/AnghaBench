#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct superblock_security_struct {int /*<<< orphan*/  behavior; scalar_t__ sid; } ;
struct super_block {TYPE_1__* s_type; struct superblock_security_struct* s_security; } ;
struct sidtab {int dummy; } ;
struct selinux_state {TYPE_4__* ss; } ;
struct policydb {struct ocontext** ocontexts; } ;
struct TYPE_7__ {int /*<<< orphan*/  behavior; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct ocontext {scalar_t__* sid; int /*<<< orphan*/ * context; TYPE_3__ v; struct ocontext* next; TYPE_2__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/  policy_rwlock; struct sidtab* sidtab; struct policydb policydb; } ;
struct TYPE_5__ {char* name; } ;

/* Variables and functions */
 size_t OCON_FSUSE ; 
 int /*<<< orphan*/  SECCLASS_DIR ; 
 int /*<<< orphan*/  SECURITY_FS_USE_GENFS ; 
 int /*<<< orphan*/  SECURITY_FS_USE_NONE ; 
 int __security_genfs_sid (struct selinux_state*,char const*,char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int sidtab_context_to_sid (struct sidtab*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int security_fs_use(struct selinux_state *state, struct super_block *sb)
{
	struct policydb *policydb;
	struct sidtab *sidtab;
	int rc = 0;
	struct ocontext *c;
	struct superblock_security_struct *sbsec = sb->s_security;
	const char *fstype = sb->s_type->name;

	read_lock(&state->ss->policy_rwlock);

	policydb = &state->ss->policydb;
	sidtab = state->ss->sidtab;

	c = policydb->ocontexts[OCON_FSUSE];
	while (c) {
		if (strcmp(fstype, c->u.name) == 0)
			break;
		c = c->next;
	}

	if (c) {
		sbsec->behavior = c->v.behavior;
		if (!c->sid[0]) {
			rc = sidtab_context_to_sid(sidtab, &c->context[0],
						   &c->sid[0]);
			if (rc)
				goto out;
		}
		sbsec->sid = c->sid[0];
	} else {
		rc = __security_genfs_sid(state, fstype, "/", SECCLASS_DIR,
					  &sbsec->sid);
		if (rc) {
			sbsec->behavior = SECURITY_FS_USE_NONE;
			rc = 0;
		} else {
			sbsec->behavior = SECURITY_FS_USE_GENFS;
		}
	}

out:
	read_unlock(&state->ss->policy_rwlock);
	return rc;
}