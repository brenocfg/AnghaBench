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
struct super_block {int s_flags; } ;
struct TYPE_2__ {int s_mount_opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ERANGE ; 
 int OCFS2_MOUNT_NOUSERXATTR ; 
 TYPE_1__* OCFS2_SB (struct super_block*) ; 
#define  OCFS2_XATTR_INDEX_POSIX_ACL_ACCESS 131 
#define  OCFS2_XATTR_INDEX_POSIX_ACL_DEFAULT 130 
#define  OCFS2_XATTR_INDEX_TRUSTED 129 
#define  OCFS2_XATTR_INDEX_USER 128 
 int SB_POSIXACL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* ocfs2_xattr_prefix (int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int ocfs2_xattr_list_entry(struct super_block *sb,
				  char *buffer, size_t size,
				  size_t *result, int type,
				  const char *name, int name_len)
{
	char *p = buffer + *result;
	const char *prefix;
	int prefix_len;
	int total_len;

	switch(type) {
	case OCFS2_XATTR_INDEX_USER:
		if (OCFS2_SB(sb)->s_mount_opt & OCFS2_MOUNT_NOUSERXATTR)
			return 0;
		break;

	case OCFS2_XATTR_INDEX_POSIX_ACL_ACCESS:
	case OCFS2_XATTR_INDEX_POSIX_ACL_DEFAULT:
		if (!(sb->s_flags & SB_POSIXACL))
			return 0;
		break;

	case OCFS2_XATTR_INDEX_TRUSTED:
		if (!capable(CAP_SYS_ADMIN))
			return 0;
		break;
	}

	prefix = ocfs2_xattr_prefix(type);
	if (!prefix)
		return 0;
	prefix_len = strlen(prefix);
	total_len = prefix_len + name_len + 1;
	*result += total_len;

	/* we are just looking for how big our buffer needs to be */
	if (!size)
		return 0;

	if (*result > size)
		return -ERANGE;

	memcpy(p, prefix, prefix_len);
	memcpy(p + prefix_len, name, name_len);
	p[prefix_len + name_len] = '\0';

	return 0;
}