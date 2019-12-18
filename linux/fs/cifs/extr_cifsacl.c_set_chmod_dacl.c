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
typedef  int u32 ;
typedef  int u16 ;
struct cifs_sid {int dummy; } ;
struct cifs_acl {void* size; void* num_aces; } ;
struct TYPE_3__ {int num_subauth; int revision; void** sub_auth; int /*<<< orphan*/ * authority; } ;
struct cifs_ace {int flags; void* size; TYPE_1__ sid; scalar_t__ access_req; int /*<<< orphan*/  type; } ;
typedef  int __u64 ;
struct TYPE_4__ {void** sub_auth; int /*<<< orphan*/ * authority; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_ALLOWED ; 
 int NUM_AUTHS ; 
 int /*<<< orphan*/  S_IRWXG ; 
 int /*<<< orphan*/  S_IRWXO ; 
 int /*<<< orphan*/  S_IRWXU ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ fill_ace_for_sid (struct cifs_ace*,struct cifs_sid*,int,int /*<<< orphan*/ ) ; 
 struct cifs_sid sid_everyone ; 
 TYPE_2__ sid_unix_NFS_mode ; 

__attribute__((used)) static int set_chmod_dacl(struct cifs_acl *pndacl, struct cifs_sid *pownersid,
			struct cifs_sid *pgrpsid, __u64 nmode, bool modefromsid)
{
	u16 size = 0;
	u32 num_aces = 0;
	struct cifs_acl *pnndacl;

	pnndacl = (struct cifs_acl *)((char *)pndacl + sizeof(struct cifs_acl));

	if (modefromsid) {
		struct cifs_ace *pntace =
			(struct cifs_ace *)((char *)pnndacl + size);
		int i;

		pntace->type = ACCESS_ALLOWED;
		pntace->flags = 0x0;
		pntace->access_req = 0;
		pntace->sid.num_subauth = 3;
		pntace->sid.revision = 1;
		for (i = 0; i < NUM_AUTHS; i++)
			pntace->sid.authority[i] =
				sid_unix_NFS_mode.authority[i];
		pntace->sid.sub_auth[0] = sid_unix_NFS_mode.sub_auth[0];
		pntace->sid.sub_auth[1] = sid_unix_NFS_mode.sub_auth[1];
		pntace->sid.sub_auth[2] = cpu_to_le32(nmode & 07777);

		/* size = 1 + 1 + 2 + 4 + 1 + 1 + 6 + (psid->num_subauth*4) */
		pntace->size = cpu_to_le16(28);
		size += 28;
		num_aces++;
	}

	size += fill_ace_for_sid((struct cifs_ace *) ((char *)pnndacl + size),
					pownersid, nmode, S_IRWXU);
	num_aces++;
	size += fill_ace_for_sid((struct cifs_ace *)((char *)pnndacl + size),
					pgrpsid, nmode, S_IRWXG);
	num_aces++;
	size += fill_ace_for_sid((struct cifs_ace *)((char *)pnndacl + size),
					 &sid_everyone, nmode, S_IRWXO);
	num_aces++;

	pndacl->num_aces = cpu_to_le32(num_aces);
	pndacl->size = cpu_to_le16(size + sizeof(struct cifs_acl));

	return 0;
}