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
struct ocfs2_xa_loc {TYPE_1__* xl_entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  xe_name_offset; int /*<<< orphan*/  xe_name_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_XATTR_ROOT_SIZE ; 
 int OCFS2_XATTR_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  def_xv ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* ocfs2_xa_offset_pointer (struct ocfs2_xa_loc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_xa_install_value_root(struct ocfs2_xa_loc *loc)
{
	int name_size = OCFS2_XATTR_SIZE(loc->xl_entry->xe_name_len);
	char *nameval_buf;

	nameval_buf = ocfs2_xa_offset_pointer(loc,
				le16_to_cpu(loc->xl_entry->xe_name_offset));
	memcpy(nameval_buf + name_size, &def_xv, OCFS2_XATTR_ROOT_SIZE);
}