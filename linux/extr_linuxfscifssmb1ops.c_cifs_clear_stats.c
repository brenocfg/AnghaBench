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
struct TYPE_3__ {int /*<<< orphan*/  num_acl_set; int /*<<< orphan*/  num_acl_get; int /*<<< orphan*/  num_locks; int /*<<< orphan*/  num_symlinks; int /*<<< orphan*/  num_hardlinks; int /*<<< orphan*/  num_fclose; int /*<<< orphan*/  num_fnext; int /*<<< orphan*/  num_ffirst; int /*<<< orphan*/  num_t2renames; int /*<<< orphan*/  num_renames; int /*<<< orphan*/  num_rmdirs; int /*<<< orphan*/  num_mkdirs; int /*<<< orphan*/  num_deletes; int /*<<< orphan*/  num_closes; int /*<<< orphan*/  num_posixmkdirs; int /*<<< orphan*/  num_posixopens; int /*<<< orphan*/  num_opens; int /*<<< orphan*/  num_oplock_brks; int /*<<< orphan*/  num_flushes; int /*<<< orphan*/  num_reads; int /*<<< orphan*/  num_writes; } ;
struct TYPE_4__ {TYPE_1__ cifs_stats; } ;
struct cifs_tcon {TYPE_2__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cifs_clear_stats(struct cifs_tcon *tcon)
{
	atomic_set(&tcon->stats.cifs_stats.num_writes, 0);
	atomic_set(&tcon->stats.cifs_stats.num_reads, 0);
	atomic_set(&tcon->stats.cifs_stats.num_flushes, 0);
	atomic_set(&tcon->stats.cifs_stats.num_oplock_brks, 0);
	atomic_set(&tcon->stats.cifs_stats.num_opens, 0);
	atomic_set(&tcon->stats.cifs_stats.num_posixopens, 0);
	atomic_set(&tcon->stats.cifs_stats.num_posixmkdirs, 0);
	atomic_set(&tcon->stats.cifs_stats.num_closes, 0);
	atomic_set(&tcon->stats.cifs_stats.num_deletes, 0);
	atomic_set(&tcon->stats.cifs_stats.num_mkdirs, 0);
	atomic_set(&tcon->stats.cifs_stats.num_rmdirs, 0);
	atomic_set(&tcon->stats.cifs_stats.num_renames, 0);
	atomic_set(&tcon->stats.cifs_stats.num_t2renames, 0);
	atomic_set(&tcon->stats.cifs_stats.num_ffirst, 0);
	atomic_set(&tcon->stats.cifs_stats.num_fnext, 0);
	atomic_set(&tcon->stats.cifs_stats.num_fclose, 0);
	atomic_set(&tcon->stats.cifs_stats.num_hardlinks, 0);
	atomic_set(&tcon->stats.cifs_stats.num_symlinks, 0);
	atomic_set(&tcon->stats.cifs_stats.num_locks, 0);
	atomic_set(&tcon->stats.cifs_stats.num_acl_get, 0);
	atomic_set(&tcon->stats.cifs_stats.num_acl_set, 0);
}