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
typedef  int umode_t ;
struct cifs_sid {int dummy; } ;
struct cifs_fattr {int cf_mode; } ;
struct cifs_acl {int /*<<< orphan*/  num_aces; int /*<<< orphan*/  size; int /*<<< orphan*/  revision; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sub_auth; } ;
struct cifs_ace {int /*<<< orphan*/  size; int /*<<< orphan*/  type; int /*<<< orphan*/  access_req; TYPE_1__ sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NOISY ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int S_IRWXUGO ; 
 int ULONG_MAX ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  access_flags_to_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ compare_sids (TYPE_1__*,struct cifs_sid*) ; 
 int /*<<< orphan*/  dump_ace (struct cifs_ace*,char*) ; 
 int /*<<< orphan*/  kfree (struct cifs_ace**) ; 
 struct cifs_ace** kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct cifs_sid sid_authusers ; 
 struct cifs_sid sid_everyone ; 
 struct cifs_sid sid_unix_NFS_mode ; 

__attribute__((used)) static void parse_dacl(struct cifs_acl *pdacl, char *end_of_acl,
		       struct cifs_sid *pownersid, struct cifs_sid *pgrpsid,
		       struct cifs_fattr *fattr, bool mode_from_special_sid)
{
	int i;
	int num_aces = 0;
	int acl_size;
	char *acl_base;
	struct cifs_ace **ppace;

	/* BB need to add parm so we can store the SID BB */

	if (!pdacl) {
		/* no DACL in the security descriptor, set
		   all the permissions for user/group/other */
		fattr->cf_mode |= S_IRWXUGO;
		return;
	}

	/* validate that we do not go past end of acl */
	if (end_of_acl < (char *)pdacl + le16_to_cpu(pdacl->size)) {
		cifs_dbg(VFS, "ACL too small to parse DACL\n");
		return;
	}

	cifs_dbg(NOISY, "DACL revision %d size %d num aces %d\n",
		 le16_to_cpu(pdacl->revision), le16_to_cpu(pdacl->size),
		 le32_to_cpu(pdacl->num_aces));

	/* reset rwx permissions for user/group/other.
	   Also, if num_aces is 0 i.e. DACL has no ACEs,
	   user/group/other have no permissions */
	fattr->cf_mode &= ~(S_IRWXUGO);

	acl_base = (char *)pdacl;
	acl_size = sizeof(struct cifs_acl);

	num_aces = le32_to_cpu(pdacl->num_aces);
	if (num_aces > 0) {
		umode_t user_mask = S_IRWXU;
		umode_t group_mask = S_IRWXG;
		umode_t other_mask = S_IRWXU | S_IRWXG | S_IRWXO;

		if (num_aces > ULONG_MAX / sizeof(struct cifs_ace *))
			return;
		ppace = kmalloc_array(num_aces, sizeof(struct cifs_ace *),
				      GFP_KERNEL);
		if (!ppace)
			return;

		for (i = 0; i < num_aces; ++i) {
			ppace[i] = (struct cifs_ace *) (acl_base + acl_size);
#ifdef CONFIG_CIFS_DEBUG2
			dump_ace(ppace[i], end_of_acl);
#endif
			if (mode_from_special_sid &&
			    (compare_sids(&(ppace[i]->sid),
					  &sid_unix_NFS_mode) == 0)) {
				/*
				 * Full permissions are:
				 * 07777 = S_ISUID | S_ISGID | S_ISVTX |
				 *         S_IRWXU | S_IRWXG | S_IRWXO
				 */
				fattr->cf_mode &= ~07777;
				fattr->cf_mode |=
					le32_to_cpu(ppace[i]->sid.sub_auth[2]);
				break;
			} else if (compare_sids(&(ppace[i]->sid), pownersid) == 0)
				access_flags_to_mode(ppace[i]->access_req,
						     ppace[i]->type,
						     &fattr->cf_mode,
						     &user_mask);
			else if (compare_sids(&(ppace[i]->sid), pgrpsid) == 0)
				access_flags_to_mode(ppace[i]->access_req,
						     ppace[i]->type,
						     &fattr->cf_mode,
						     &group_mask);
			else if (compare_sids(&(ppace[i]->sid), &sid_everyone) == 0)
				access_flags_to_mode(ppace[i]->access_req,
						     ppace[i]->type,
						     &fattr->cf_mode,
						     &other_mask);
			else if (compare_sids(&(ppace[i]->sid), &sid_authusers) == 0)
				access_flags_to_mode(ppace[i]->access_req,
						     ppace[i]->type,
						     &fattr->cf_mode,
						     &other_mask);


/*			memcpy((void *)(&(cifscred->aces[i])),
				(void *)ppace[i],
				sizeof(struct cifs_ace)); */

			acl_base = (char *)ppace[i];
			acl_size = le16_to_cpu(ppace[i]->size);
		}

		kfree(ppace);
	}

	return;
}