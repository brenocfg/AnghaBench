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
struct user_namespace {int dummy; } ;
struct posix_acl_xattr_header {scalar_t__ a_version; } ;
struct posix_acl_xattr_entry {int /*<<< orphan*/  e_id; int /*<<< orphan*/  e_perm; int /*<<< orphan*/  e_tag; } ;
struct posix_acl_entry {int e_tag; int /*<<< orphan*/  e_gid; int /*<<< orphan*/  e_uid; void* e_perm; } ;
struct posix_acl {struct posix_acl_entry* a_entries; } ;

/* Variables and functions */
#define  ACL_GROUP 133 
#define  ACL_GROUP_OBJ 132 
#define  ACL_MASK 131 
#define  ACL_OTHER 130 
#define  ACL_USER 129 
#define  ACL_USER_OBJ 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct posix_acl* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  POSIX_ACL_XATTR_VERSION ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 struct posix_acl* posix_acl_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_xattr_count (size_t) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

struct posix_acl *
posix_acl_from_xattr(struct user_namespace *user_ns,
		     const void *value, size_t size)
{
	const struct posix_acl_xattr_header *header = value;
	const struct posix_acl_xattr_entry *entry = (const void *)(header + 1), *end;
	int count;
	struct posix_acl *acl;
	struct posix_acl_entry *acl_e;

	if (!value)
		return NULL;
	if (size < sizeof(struct posix_acl_xattr_header))
		 return ERR_PTR(-EINVAL);
	if (header->a_version != cpu_to_le32(POSIX_ACL_XATTR_VERSION))
		return ERR_PTR(-EOPNOTSUPP);

	count = posix_acl_xattr_count(size);
	if (count < 0)
		return ERR_PTR(-EINVAL);
	if (count == 0)
		return NULL;
	
	acl = posix_acl_alloc(count, GFP_NOFS);
	if (!acl)
		return ERR_PTR(-ENOMEM);
	acl_e = acl->a_entries;
	
	for (end = entry + count; entry != end; acl_e++, entry++) {
		acl_e->e_tag  = le16_to_cpu(entry->e_tag);
		acl_e->e_perm = le16_to_cpu(entry->e_perm);

		switch(acl_e->e_tag) {
			case ACL_USER_OBJ:
			case ACL_GROUP_OBJ:
			case ACL_MASK:
			case ACL_OTHER:
				break;

			case ACL_USER:
				acl_e->e_uid =
					make_kuid(user_ns,
						  le32_to_cpu(entry->e_id));
				if (!uid_valid(acl_e->e_uid))
					goto fail;
				break;
			case ACL_GROUP:
				acl_e->e_gid =
					make_kgid(user_ns,
						  le32_to_cpu(entry->e_id));
				if (!gid_valid(acl_e->e_gid))
					goto fail;
				break;

			default:
				goto fail;
		}
	}
	return acl;

fail:
	posix_acl_release(acl);
	return ERR_PTR(-EINVAL);
}