#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct f2fs_sb_info {TYPE_2__* raw_super; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct f2fs_attr {int offset; TYPE_1__ attr; int /*<<< orphan*/  struct_type; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int hot_ext_count; int /*<<< orphan*/  extension_count; int /*<<< orphan*/  extension_list; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t F2FS_EXTENSION_LEN ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned char* __struct_ptr (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __u8 (char*) ; 
 char** extlist ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int snprintf (char*,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t f2fs_sbi_show(struct f2fs_attr *a,
			struct f2fs_sb_info *sbi, char *buf)
{
	unsigned char *ptr = NULL;
	unsigned int *ui;

	ptr = __struct_ptr(sbi, a->struct_type);
	if (!ptr)
		return -EINVAL;

	if (!strcmp(a->attr.name, "extension_list")) {
		__u8 (*extlist)[F2FS_EXTENSION_LEN] =
					sbi->raw_super->extension_list;
		int cold_count = le32_to_cpu(sbi->raw_super->extension_count);
		int hot_count = sbi->raw_super->hot_ext_count;
		int len = 0, i;

		len += snprintf(buf + len, PAGE_SIZE - len,
						"cold file extension:\n");
		for (i = 0; i < cold_count; i++)
			len += snprintf(buf + len, PAGE_SIZE - len, "%s\n",
								extlist[i]);

		len += snprintf(buf + len, PAGE_SIZE - len,
						"hot file extension:\n");
		for (i = cold_count; i < cold_count + hot_count; i++)
			len += snprintf(buf + len, PAGE_SIZE - len, "%s\n",
								extlist[i]);
		return len;
	}

	ui = (unsigned int *)(ptr + a->offset);

	return snprintf(buf, PAGE_SIZE, "%u\n", *ui);
}