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
typedef  scalar_t__ uint32_t ;
struct posix_acl {TYPE_1__* a_entries; } ;
struct jffs2_acl_header {int /*<<< orphan*/  a_version; } ;
struct jffs2_acl_entry_short {int dummy; } ;
struct jffs2_acl_entry {int /*<<< orphan*/  e_id; int /*<<< orphan*/  e_perm; int /*<<< orphan*/  e_tag; } ;
struct TYPE_2__ {int e_tag; int /*<<< orphan*/  e_gid; int /*<<< orphan*/  e_uid; void* e_perm; } ;

/* Variables and functions */
#define  ACL_GROUP 133 
#define  ACL_GROUP_OBJ 132 
#define  ACL_MASK 131 
#define  ACL_OTHER 130 
#define  ACL_USER 129 
#define  ACL_USER_OBJ 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct posix_acl* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ JFFS2_ACL_VERSION ; 
 int /*<<< orphan*/  JFFS2_WARNING (char*,scalar_t__) ; 
 int /*<<< orphan*/  init_user_ns ; 
 void* je16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ je32_to_cpu (int /*<<< orphan*/ ) ; 
 int jffs2_acl_count (size_t) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ *,scalar_t__) ; 
 struct posix_acl* posix_acl_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 

__attribute__((used)) static struct posix_acl *jffs2_acl_from_medium(void *value, size_t size)
{
	void *end = value + size;
	struct jffs2_acl_header *header = value;
	struct jffs2_acl_entry *entry;
	struct posix_acl *acl;
	uint32_t ver;
	int i, count;

	if (!value)
		return NULL;
	if (size < sizeof(struct jffs2_acl_header))
		return ERR_PTR(-EINVAL);
	ver = je32_to_cpu(header->a_version);
	if (ver != JFFS2_ACL_VERSION) {
		JFFS2_WARNING("Invalid ACL version. (=%u)\n", ver);
		return ERR_PTR(-EINVAL);
	}

	value += sizeof(struct jffs2_acl_header);
	count = jffs2_acl_count(size);
	if (count < 0)
		return ERR_PTR(-EINVAL);
	if (count == 0)
		return NULL;

	acl = posix_acl_alloc(count, GFP_KERNEL);
	if (!acl)
		return ERR_PTR(-ENOMEM);

	for (i=0; i < count; i++) {
		entry = value;
		if (value + sizeof(struct jffs2_acl_entry_short) > end)
			goto fail;
		acl->a_entries[i].e_tag = je16_to_cpu(entry->e_tag);
		acl->a_entries[i].e_perm = je16_to_cpu(entry->e_perm);
		switch (acl->a_entries[i].e_tag) {
			case ACL_USER_OBJ:
			case ACL_GROUP_OBJ:
			case ACL_MASK:
			case ACL_OTHER:
				value += sizeof(struct jffs2_acl_entry_short);
				break;

			case ACL_USER:
				value += sizeof(struct jffs2_acl_entry);
				if (value > end)
					goto fail;
				acl->a_entries[i].e_uid =
					make_kuid(&init_user_ns,
						  je32_to_cpu(entry->e_id));
				break;
			case ACL_GROUP:
				value += sizeof(struct jffs2_acl_entry);
				if (value > end)
					goto fail;
				acl->a_entries[i].e_gid =
					make_kgid(&init_user_ns,
						  je32_to_cpu(entry->e_id));
				break;

			default:
				goto fail;
		}
	}
	if (value != end)
		goto fail;
	return acl;
 fail:
	posix_acl_release(acl);
	return ERR_PTR(-EINVAL);
}