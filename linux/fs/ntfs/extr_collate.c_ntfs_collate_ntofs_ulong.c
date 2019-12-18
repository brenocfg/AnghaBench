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
typedef  int /*<<< orphan*/  ntfs_volume ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ le32_to_cpup (void const*) ; 
 int /*<<< orphan*/  ntfs_debug (char*,...) ; 

__attribute__((used)) static int ntfs_collate_ntofs_ulong(ntfs_volume *vol,
		const void *data1, const int data1_len,
		const void *data2, const int data2_len)
{
	int rc;
	u32 d1, d2;

	ntfs_debug("Entering.");
	// FIXME:  We don't really want to bug here.
	BUG_ON(data1_len != data2_len);
	BUG_ON(data1_len != 4);
	d1 = le32_to_cpup(data1);
	d2 = le32_to_cpup(data2);
	if (d1 < d2)
		rc = -1;
	else {
		if (d1 == d2)
			rc = 0;
		else
			rc = 1;
	}
	ntfs_debug("Done, returning %i", rc);
	return rc;
}