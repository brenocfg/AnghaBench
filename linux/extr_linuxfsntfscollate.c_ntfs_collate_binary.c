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
typedef  int /*<<< orphan*/  ntfs_volume ;

/* Variables and functions */
 int memcmp (void const*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int const,int const) ; 
 int /*<<< orphan*/  ntfs_debug (char*,...) ; 

__attribute__((used)) static int ntfs_collate_binary(ntfs_volume *vol,
		const void *data1, const int data1_len,
		const void *data2, const int data2_len)
{
	int rc;

	ntfs_debug("Entering.");
	rc = memcmp(data1, data2, min(data1_len, data2_len));
	if (!rc && (data1_len != data2_len)) {
		if (data1_len < data2_len)
			rc = -1;
		else
			rc = 1;
	}
	ntfs_debug("Done, returning %i", rc);
	return rc;
}