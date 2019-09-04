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
typedef  size_t u32 ;
struct log_entry {scalar_t__ seq; scalar_t__ old_map; scalar_t__ new_map; scalar_t__ lba; } ;
struct free_entry {int dummy; } ;
struct arena_info {size_t nfree; TYPE_1__* freelist; } ;
struct TYPE_2__ {int sub; size_t block; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LOG_NEW_ENT ; 
 int /*<<< orphan*/  LOG_OLD_ENT ; 
 int arena_clear_freelist_error (struct arena_info*,size_t) ; 
 int btt_log_read (struct arena_info*,size_t,struct log_entry*,int /*<<< orphan*/ ) ; 
 int btt_map_read (struct arena_info*,size_t,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int btt_map_write (struct arena_info*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ent_e_flag (scalar_t__) ; 
 TYPE_1__* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  nd_inc_seq (size_t) ; 
 int /*<<< orphan*/  to_dev (struct arena_info*) ; 

__attribute__((used)) static int btt_freelist_init(struct arena_info *arena)
{
	int old, new, ret;
	u32 i, map_entry;
	struct log_entry log_new, log_old;

	arena->freelist = kcalloc(arena->nfree, sizeof(struct free_entry),
					GFP_KERNEL);
	if (!arena->freelist)
		return -ENOMEM;

	for (i = 0; i < arena->nfree; i++) {
		old = btt_log_read(arena, i, &log_old, LOG_OLD_ENT);
		if (old < 0)
			return old;

		new = btt_log_read(arena, i, &log_new, LOG_NEW_ENT);
		if (new < 0)
			return new;

		/* sub points to the next one to be overwritten */
		arena->freelist[i].sub = 1 - new;
		arena->freelist[i].seq = nd_inc_seq(le32_to_cpu(log_new.seq));
		arena->freelist[i].block = le32_to_cpu(log_new.old_map);

		/*
		 * FIXME: if error clearing fails during init, we want to make
		 * the BTT read-only
		 */
		if (ent_e_flag(log_new.old_map)) {
			ret = arena_clear_freelist_error(arena, i);
			if (ret)
				dev_err_ratelimited(to_dev(arena),
					"Unable to clear known errors\n");
		}

		/* This implies a newly created or untouched flog entry */
		if (log_new.old_map == log_new.new_map)
			continue;

		/* Check if map recovery is needed */
		ret = btt_map_read(arena, le32_to_cpu(log_new.lba), &map_entry,
				NULL, NULL, 0);
		if (ret)
			return ret;
		if ((le32_to_cpu(log_new.new_map) != map_entry) &&
				(le32_to_cpu(log_new.old_map) == map_entry)) {
			/*
			 * Last transaction wrote the flog, but wasn't able
			 * to complete the map write. So fix up the map.
			 */
			ret = btt_map_write(arena, le32_to_cpu(log_new.lba),
					le32_to_cpu(log_new.new_map), 0, 0, 0);
			if (ret)
				return ret;
		}
	}

	return 0;
}