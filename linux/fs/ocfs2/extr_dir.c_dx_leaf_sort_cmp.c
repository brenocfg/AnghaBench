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
typedef  scalar_t__ u32 ;
struct ocfs2_dx_entry {int /*<<< orphan*/  dx_minor_hash; int /*<<< orphan*/  dx_major_hash; } ;

/* Variables and functions */
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dx_leaf_sort_cmp(const void *a, const void *b)
{
	const struct ocfs2_dx_entry *entry1 = a;
	const struct ocfs2_dx_entry *entry2 = b;
	u32 major_hash1 = le32_to_cpu(entry1->dx_major_hash);
	u32 major_hash2 = le32_to_cpu(entry2->dx_major_hash);
	u32 minor_hash1 = le32_to_cpu(entry1->dx_minor_hash);
	u32 minor_hash2 = le32_to_cpu(entry2->dx_minor_hash);

	if (major_hash1 > major_hash2)
		return 1;
	if (major_hash1 < major_hash2)
		return -1;

	/*
	 * It is not strictly necessary to sort by minor
	 */
	if (minor_hash1 > minor_hash2)
		return 1;
	if (minor_hash1 < minor_hash2)
		return -1;
	return 0;
}