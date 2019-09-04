#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  ntfschar ;
struct TYPE_4__ {int /*<<< orphan*/  file_name_length; int /*<<< orphan*/  file_name; } ;
typedef  int /*<<< orphan*/  IGNORE_CASE_BOOL ;
typedef  TYPE_1__ FILE_NAME_ATTR ;

/* Variables and functions */
 int ntfs_collate_names (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ; 

int ntfs_file_compare_values(FILE_NAME_ATTR *file_name_attr1,
		FILE_NAME_ATTR *file_name_attr2,
		const int err_val, const IGNORE_CASE_BOOL ic,
		const ntfschar *upcase, const u32 upcase_len)
{
	return ntfs_collate_names((ntfschar*)&file_name_attr1->file_name,
			file_name_attr1->file_name_length,
			(ntfschar*)&file_name_attr2->file_name,
			file_name_attr2->file_name_length,
			err_val, ic, upcase, upcase_len);
}