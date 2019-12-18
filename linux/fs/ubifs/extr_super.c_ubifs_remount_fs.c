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
struct TYPE_4__ {scalar_t__ taken_empty_lebs; } ;
struct TYPE_3__ {int /*<<< orphan*/ * buf; } ;
struct ubifs_info {int bulk_read; TYPE_2__ lst; int /*<<< orphan*/  need_recovery; int /*<<< orphan*/  bu_mutex; TYPE_1__ bu; scalar_t__ ro_error; scalar_t__ ro_mount; scalar_t__ ro_media; } ;
struct super_block {int /*<<< orphan*/  s_flags; struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int EROFS ; 
 int SB_RDONLY ; 
 int /*<<< orphan*/  bu_init (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_gen (char*,...) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_filesystem (struct super_block*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*) ; 
 int /*<<< orphan*/  ubifs_msg (struct ubifs_info*,char*) ; 
 int ubifs_parse_options (struct ubifs_info*,char*,int) ; 
 int /*<<< orphan*/  ubifs_remount_ro (struct ubifs_info*) ; 
 int ubifs_remount_rw (struct ubifs_info*) ; 

__attribute__((used)) static int ubifs_remount_fs(struct super_block *sb, int *flags, char *data)
{
	int err;
	struct ubifs_info *c = sb->s_fs_info;

	sync_filesystem(sb);
	dbg_gen("old flags %#lx, new flags %#x", sb->s_flags, *flags);

	err = ubifs_parse_options(c, data, 1);
	if (err) {
		ubifs_err(c, "invalid or unknown remount parameter");
		return err;
	}

	if (c->ro_mount && !(*flags & SB_RDONLY)) {
		if (c->ro_error) {
			ubifs_msg(c, "cannot re-mount R/W due to prior errors");
			return -EROFS;
		}
		if (c->ro_media) {
			ubifs_msg(c, "cannot re-mount R/W - UBI volume is R/O");
			return -EROFS;
		}
		err = ubifs_remount_rw(c);
		if (err)
			return err;
	} else if (!c->ro_mount && (*flags & SB_RDONLY)) {
		if (c->ro_error) {
			ubifs_msg(c, "cannot re-mount R/O due to prior errors");
			return -EROFS;
		}
		ubifs_remount_ro(c);
	}

	if (c->bulk_read == 1)
		bu_init(c);
	else {
		dbg_gen("disable bulk-read");
		mutex_lock(&c->bu_mutex);
		kfree(c->bu.buf);
		c->bu.buf = NULL;
		mutex_unlock(&c->bu_mutex);
	}

	if (!c->need_recovery)
		ubifs_assert(c, c->lst.taken_empty_lebs > 0);

	return 0;
}