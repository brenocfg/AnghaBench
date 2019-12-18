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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_xattr_entry {int dummy; } ;
struct ocfs2_xa_loc {int /*<<< orphan*/ * xl_entry; TYPE_1__* xl_header; } ;
struct TYPE_2__ {int /*<<< orphan*/  xh_count; int /*<<< orphan*/ * xh_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ocfs2_xa_block_add_entry(struct ocfs2_xa_loc *loc, u32 name_hash)
{
	int count = le16_to_cpu(loc->xl_header->xh_count);
	loc->xl_entry = &(loc->xl_header->xh_entries[count]);
	le16_add_cpu(&loc->xl_header->xh_count, 1);
	memset(loc->xl_entry, 0, sizeof(struct ocfs2_xattr_entry));
}