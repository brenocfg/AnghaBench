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
struct jffs2_acl_header {int dummy; } ;
struct jffs2_acl_entry_short {int dummy; } ;
struct jffs2_acl_entry {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static size_t jffs2_acl_size(int count)
{
	if (count <= 4) {
		return sizeof(struct jffs2_acl_header)
		       + count * sizeof(struct jffs2_acl_entry_short);
	} else {
		return sizeof(struct jffs2_acl_header)
		       + 4 * sizeof(struct jffs2_acl_entry_short)
		       + (count - 4) * sizeof(struct jffs2_acl_entry);
	}
}