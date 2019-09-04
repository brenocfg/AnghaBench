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
struct f2fs_sb_info {TYPE_2__* sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct f2fs_attr {scalar_t__ struct_type; TYPE_1__ attr; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  s_umount; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ GC_THREAD ; 
 int /*<<< orphan*/  __sbi_store (struct f2fs_attr*,struct f2fs_sb_info*,char const*,size_t) ; 
 int /*<<< orphan*/  down_read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t f2fs_sbi_store(struct f2fs_attr *a,
			struct f2fs_sb_info *sbi,
			const char *buf, size_t count)
{
	ssize_t ret;
	bool gc_entry = (!strcmp(a->attr.name, "gc_urgent") ||
					a->struct_type == GC_THREAD);

	if (gc_entry) {
		if (!down_read_trylock(&sbi->sb->s_umount))
			return -EAGAIN;
	}
	ret = __sbi_store(a, sbi, buf, count);
	if (gc_entry)
		up_read(&sbi->sb->s_umount);

	return ret;
}