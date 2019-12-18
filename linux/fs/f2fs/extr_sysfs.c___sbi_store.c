#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct f2fs_sb_info {unsigned long segs_per_sec; unsigned long gc_mode; int iostat_enable; TYPE_1__* gc_thread; int /*<<< orphan*/  stat_lock; scalar_t__ user_block_count; int /*<<< orphan*/  reserved_blocks; int /*<<< orphan*/  current_reserved_blocks; int /*<<< orphan*/  sb_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct f2fs_attr {scalar_t__ struct_type; int offset; TYPE_2__ attr; } ;
typedef  size_t ssize_t ;
struct TYPE_6__ {scalar_t__ root_reserved_blocks; } ;
struct TYPE_4__ {int gc_wake; int /*<<< orphan*/  gc_wait_queue_head; } ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ F2FS_EXTENSION_LEN ; 
 TYPE_3__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 scalar_t__ FAULT_INFO_RATE ; 
 scalar_t__ FAULT_INFO_TYPE ; 
 int FAULT_MAX ; 
 unsigned long GC_IDLE_CB ; 
 unsigned long GC_IDLE_GREEDY ; 
 void* GC_NORMAL ; 
 unsigned long GC_URGENT ; 
 unsigned long MAX_PLIST_NUM ; 
 scalar_t__ RESERVED_BLOCKS ; 
 unsigned long UINT_MAX ; 
 unsigned char* __struct_ptr (struct f2fs_sb_info*,scalar_t__) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 size_t f2fs_commit_super (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_reset_iostat (struct f2fs_sb_info*) ; 
 size_t f2fs_update_extension_list (struct f2fs_sb_info*,char const*,int,int) ; 
 size_t kstrtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skip_spaces (char const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strim (char*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 scalar_t__ valid_user_blocks (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  wake_up_discard_thread (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t __sbi_store(struct f2fs_attr *a,
			struct f2fs_sb_info *sbi,
			const char *buf, size_t count)
{
	unsigned char *ptr;
	unsigned long t;
	unsigned int *ui;
	ssize_t ret;

	ptr = __struct_ptr(sbi, a->struct_type);
	if (!ptr)
		return -EINVAL;

	if (!strcmp(a->attr.name, "extension_list")) {
		const char *name = strim((char *)buf);
		bool set = true, hot;

		if (!strncmp(name, "[h]", 3))
			hot = true;
		else if (!strncmp(name, "[c]", 3))
			hot = false;
		else
			return -EINVAL;

		name += 3;

		if (*name == '!') {
			name++;
			set = false;
		}

		if (strlen(name) >= F2FS_EXTENSION_LEN)
			return -EINVAL;

		down_write(&sbi->sb_lock);

		ret = f2fs_update_extension_list(sbi, name, hot, set);
		if (ret)
			goto out;

		ret = f2fs_commit_super(sbi, false);
		if (ret)
			f2fs_update_extension_list(sbi, name, hot, !set);
out:
		up_write(&sbi->sb_lock);
		return ret ? ret : count;
	}

	ui = (unsigned int *)(ptr + a->offset);

	ret = kstrtoul(skip_spaces(buf), 0, &t);
	if (ret < 0)
		return ret;
#ifdef CONFIG_F2FS_FAULT_INJECTION
	if (a->struct_type == FAULT_INFO_TYPE && t >= (1 << FAULT_MAX))
		return -EINVAL;
	if (a->struct_type == FAULT_INFO_RATE && t >= UINT_MAX)
		return -EINVAL;
#endif
	if (a->struct_type == RESERVED_BLOCKS) {
		spin_lock(&sbi->stat_lock);
		if (t > (unsigned long)(sbi->user_block_count -
				F2FS_OPTION(sbi).root_reserved_blocks)) {
			spin_unlock(&sbi->stat_lock);
			return -EINVAL;
		}
		*ui = t;
		sbi->current_reserved_blocks = min(sbi->reserved_blocks,
				sbi->user_block_count - valid_user_blocks(sbi));
		spin_unlock(&sbi->stat_lock);
		return count;
	}

	if (!strcmp(a->attr.name, "discard_granularity")) {
		if (t == 0 || t > MAX_PLIST_NUM)
			return -EINVAL;
		if (t == *ui)
			return count;
		*ui = t;
		return count;
	}

	if (!strcmp(a->attr.name, "migration_granularity")) {
		if (t == 0 || t > sbi->segs_per_sec)
			return -EINVAL;
	}

	if (!strcmp(a->attr.name, "trim_sections"))
		return -EINVAL;

	if (!strcmp(a->attr.name, "gc_urgent")) {
		if (t >= 1) {
			sbi->gc_mode = GC_URGENT;
			if (sbi->gc_thread) {
				sbi->gc_thread->gc_wake = 1;
				wake_up_interruptible_all(
					&sbi->gc_thread->gc_wait_queue_head);
				wake_up_discard_thread(sbi, true);
			}
		} else {
			sbi->gc_mode = GC_NORMAL;
		}
		return count;
	}
	if (!strcmp(a->attr.name, "gc_idle")) {
		if (t == GC_IDLE_CB)
			sbi->gc_mode = GC_IDLE_CB;
		else if (t == GC_IDLE_GREEDY)
			sbi->gc_mode = GC_IDLE_GREEDY;
		else
			sbi->gc_mode = GC_NORMAL;
		return count;
	}


	if (!strcmp(a->attr.name, "iostat_enable")) {
		sbi->iostat_enable = !!t;
		if (!sbi->iostat_enable)
			f2fs_reset_iostat(sbi);
		return count;
	}

	*ui = (unsigned int)t;

	return count;
}