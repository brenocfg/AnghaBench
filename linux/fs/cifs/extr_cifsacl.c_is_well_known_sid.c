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
typedef  int uint32_t ;
struct cifs_sid {int num_subauth; scalar_t__ revision; scalar_t__* authority; scalar_t__* sub_auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int NUM_AUTHS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int le32_to_cpu (scalar_t__) ; 
 struct cifs_sid sid_unix_NFS_groups ; 
 struct cifs_sid sid_unix_NFS_users ; 
 struct cifs_sid sid_unix_groups ; 
 struct cifs_sid sid_unix_users ; 

__attribute__((used)) static bool
is_well_known_sid(const struct cifs_sid *psid, uint32_t *puid, bool is_group)
{
	int i;
	int num_subauth;
	const struct cifs_sid *pwell_known_sid;

	if (!psid || (puid == NULL))
		return false;

	num_subauth = psid->num_subauth;

	/* check if Mac (or Windows NFS) vs. Samba format for Unix owner SID */
	if (num_subauth == 2) {
		if (is_group)
			pwell_known_sid = &sid_unix_groups;
		else
			pwell_known_sid = &sid_unix_users;
	} else if (num_subauth == 3) {
		if (is_group)
			pwell_known_sid = &sid_unix_NFS_groups;
		else
			pwell_known_sid = &sid_unix_NFS_users;
	} else
		return false;

	/* compare the revision */
	if (psid->revision != pwell_known_sid->revision)
		return false;

	/* compare all of the six auth values */
	for (i = 0; i < NUM_AUTHS; ++i) {
		if (psid->authority[i] != pwell_known_sid->authority[i]) {
			cifs_dbg(FYI, "auth %d did not match\n", i);
			return false;
		}
	}

	if (num_subauth == 2) {
		if (psid->sub_auth[0] != pwell_known_sid->sub_auth[0])
			return false;

		*puid = le32_to_cpu(psid->sub_auth[1]);
	} else /* 3 subauths, ie Windows/Mac style */ {
		*puid = le32_to_cpu(psid->sub_auth[0]);
		if ((psid->sub_auth[0] != pwell_known_sid->sub_auth[0]) ||
		    (psid->sub_auth[1] != pwell_known_sid->sub_auth[1]))
			return false;

		*puid = le32_to_cpu(psid->sub_auth[2]);
	}

	cifs_dbg(FYI, "Unix UID %d returned from SID\n", *puid);
	return true; /* well known sid found, uid returned */
}