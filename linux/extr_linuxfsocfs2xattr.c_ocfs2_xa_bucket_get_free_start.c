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
struct ocfs2_xattr_bucket {int dummy; } ;
struct ocfs2_xa_loc {struct ocfs2_xattr_bucket* xl_storage; } ;
struct TYPE_2__ {int /*<<< orphan*/  xh_free_start; } ;

/* Variables and functions */
 TYPE_1__* bucket_xh (struct ocfs2_xattr_bucket*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_xa_bucket_get_free_start(struct ocfs2_xa_loc *loc)
{
	struct ocfs2_xattr_bucket *bucket = loc->xl_storage;
	return le16_to_cpu(bucket_xh(bucket)->xh_free_start);
}