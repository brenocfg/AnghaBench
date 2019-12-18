#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_9__ {scalar_t__ fmask; scalar_t__ dmask; int on_errors; scalar_t__ mft_zone_multiplier; TYPE_1__* nls_map; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  TYPE_2__ ntfs_volume ;
struct TYPE_10__ {int val; scalar_t__ str; } ;
struct TYPE_8__ {scalar_t__ charset; } ;

/* Variables and functions */
 TYPE_2__* NTFS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ NVolCaseSensitive (TYPE_2__*) ; 
 scalar_t__ NVolShowSystemFiles (TYPE_2__*) ; 
 int /*<<< orphan*/  NVolSparseEnabled (TYPE_2__*) ; 
 scalar_t__ from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 TYPE_3__* on_errors_arr ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

int ntfs_show_options(struct seq_file *sf, struct dentry *root)
{
	ntfs_volume *vol = NTFS_SB(root->d_sb);
	int i;

	seq_printf(sf, ",uid=%i", from_kuid_munged(&init_user_ns, vol->uid));
	seq_printf(sf, ",gid=%i", from_kgid_munged(&init_user_ns, vol->gid));
	if (vol->fmask == vol->dmask)
		seq_printf(sf, ",umask=0%o", vol->fmask);
	else {
		seq_printf(sf, ",fmask=0%o", vol->fmask);
		seq_printf(sf, ",dmask=0%o", vol->dmask);
	}
	seq_printf(sf, ",nls=%s", vol->nls_map->charset);
	if (NVolCaseSensitive(vol))
		seq_printf(sf, ",case_sensitive");
	if (NVolShowSystemFiles(vol))
		seq_printf(sf, ",show_sys_files");
	if (!NVolSparseEnabled(vol))
		seq_printf(sf, ",disable_sparse");
	for (i = 0; on_errors_arr[i].val; i++) {
		if (on_errors_arr[i].val & vol->on_errors)
			seq_printf(sf, ",errors=%s", on_errors_arr[i].str);
	}
	seq_printf(sf, ",mft_zone_multiplier=%i", vol->mft_zone_multiplier);
	return 0;
}