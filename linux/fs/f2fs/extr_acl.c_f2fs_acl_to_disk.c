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
struct posix_acl {int a_count; TYPE_1__* a_entries; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_acl_header {void* a_version; } ;
struct f2fs_acl_entry_short {int dummy; } ;
struct f2fs_acl_entry {void* e_id; void* e_perm; void* e_tag; } ;
struct TYPE_2__ {int e_tag; int e_perm; int /*<<< orphan*/  e_gid; int /*<<< orphan*/  e_uid; } ;

/* Variables and functions */
#define  ACL_GROUP 133 
#define  ACL_GROUP_OBJ 132 
#define  ACL_MASK 131 
#define  ACL_OTHER 130 
#define  ACL_USER 129 
#define  ACL_USER_OBJ 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F2FS_ACL_VERSION ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 size_t f2fs_acl_size (int) ; 
 struct f2fs_acl_header* f2fs_kmalloc (struct f2fs_sb_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  kvfree (struct f2fs_acl_header*) ; 

__attribute__((used)) static void *f2fs_acl_to_disk(struct f2fs_sb_info *sbi,
				const struct posix_acl *acl, size_t *size)
{
	struct f2fs_acl_header *f2fs_acl;
	struct f2fs_acl_entry *entry;
	int i;

	f2fs_acl = f2fs_kmalloc(sbi, sizeof(struct f2fs_acl_header) +
			acl->a_count * sizeof(struct f2fs_acl_entry),
			GFP_NOFS);
	if (!f2fs_acl)
		return ERR_PTR(-ENOMEM);

	f2fs_acl->a_version = cpu_to_le32(F2FS_ACL_VERSION);
	entry = (struct f2fs_acl_entry *)(f2fs_acl + 1);

	for (i = 0; i < acl->a_count; i++) {

		entry->e_tag  = cpu_to_le16(acl->a_entries[i].e_tag);
		entry->e_perm = cpu_to_le16(acl->a_entries[i].e_perm);

		switch (acl->a_entries[i].e_tag) {
		case ACL_USER:
			entry->e_id = cpu_to_le32(
					from_kuid(&init_user_ns,
						acl->a_entries[i].e_uid));
			entry = (struct f2fs_acl_entry *)((char *)entry +
					sizeof(struct f2fs_acl_entry));
			break;
		case ACL_GROUP:
			entry->e_id = cpu_to_le32(
					from_kgid(&init_user_ns,
						acl->a_entries[i].e_gid));
			entry = (struct f2fs_acl_entry *)((char *)entry +
					sizeof(struct f2fs_acl_entry));
			break;
		case ACL_USER_OBJ:
		case ACL_GROUP_OBJ:
		case ACL_MASK:
		case ACL_OTHER:
			entry = (struct f2fs_acl_entry *)((char *)entry +
					sizeof(struct f2fs_acl_entry_short));
			break;
		default:
			goto fail;
		}
	}
	*size = f2fs_acl_size(acl->a_count);
	return (void *)f2fs_acl;

fail:
	kvfree(f2fs_acl);
	return ERR_PTR(-EINVAL);
}