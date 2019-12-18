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
struct posix_acl_xattr_entry {scalar_t__ e_id; int /*<<< orphan*/  e_tag; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
#define  ACL_GROUP 129 
#define  ACL_USER 128 
 int /*<<< orphan*/  POSIX_ACL_XATTR_VERSION ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kgid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  make_kgid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int posix_acl_xattr_count (size_t) ; 

__attribute__((used)) static void posix_acl_fix_xattr_userns(
	struct user_namespace *to, struct user_namespace *from,
	void *value, size_t size)
{
	struct posix_acl_xattr_header *header = value;
	struct posix_acl_xattr_entry *entry = (void *)(header + 1), *end;
	int count;
	kuid_t uid;
	kgid_t gid;

	if (!value)
		return;
	if (size < sizeof(struct posix_acl_xattr_header))
		return;
	if (header->a_version != cpu_to_le32(POSIX_ACL_XATTR_VERSION))
		return;

	count = posix_acl_xattr_count(size);
	if (count < 0)
		return;
	if (count == 0)
		return;

	for (end = entry + count; entry != end; entry++) {
		switch(le16_to_cpu(entry->e_tag)) {
		case ACL_USER:
			uid = make_kuid(from, le32_to_cpu(entry->e_id));
			entry->e_id = cpu_to_le32(from_kuid(to, uid));
			break;
		case ACL_GROUP:
			gid = make_kgid(from, le32_to_cpu(entry->e_id));
			entry->e_id = cpu_to_le32(from_kgid(to, gid));
			break;
		default:
			break;
		}
	}
}