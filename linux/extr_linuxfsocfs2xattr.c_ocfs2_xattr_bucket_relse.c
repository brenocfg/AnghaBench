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
struct ocfs2_xattr_bucket {int bu_blocks; int /*<<< orphan*/ ** bu_bhs; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_xattr_bucket_relse(struct ocfs2_xattr_bucket *bucket)
{
	int i;

	for (i = 0; i < bucket->bu_blocks; i++) {
		brelse(bucket->bu_bhs[i]);
		bucket->bu_bhs[i] = NULL;
	}
}