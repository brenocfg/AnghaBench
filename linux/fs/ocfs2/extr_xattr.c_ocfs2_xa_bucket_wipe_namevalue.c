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
struct ocfs2_xa_loc {int /*<<< orphan*/  xl_entry; TYPE_1__* xl_header; } ;
struct TYPE_2__ {int /*<<< orphan*/  xh_name_value_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namevalue_size_xe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_xa_bucket_wipe_namevalue(struct ocfs2_xa_loc *loc)
{
	le16_add_cpu(&loc->xl_header->xh_name_value_len,
		     -namevalue_size_xe(loc->xl_entry));
}