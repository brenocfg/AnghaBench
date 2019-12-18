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
typedef  int uint32_t ;
struct lm_lockstruct {int ls_first; int /*<<< orphan*/  ls_dlm; scalar_t__ ls_recover_flags; int /*<<< orphan*/ * ls_lvb_bits; int /*<<< orphan*/ * ls_recover_result; int /*<<< orphan*/ * ls_recover_submit; scalar_t__ ls_recover_size; scalar_t__ ls_recover_block; scalar_t__ ls_recover_start; scalar_t__ ls_recover_mount; int /*<<< orphan*/  ls_recover_spin; } ;
struct gfs2_sbd {scalar_t__ sd_flags; int /*<<< orphan*/  sd_control_work; struct lm_lockstruct sd_lockstruct; } ;
typedef  int /*<<< orphan*/  cluster ;

/* Variables and functions */
 int /*<<< orphan*/  DFL_FIRST_MOUNT ; 
 int /*<<< orphan*/  DFL_NO_DLM_OPS ; 
 int DLM_LSFL_FS ; 
 int DLM_LSFL_NEWEXCL ; 
 int EINVAL ; 
 int /*<<< orphan*/  GDLM_LVB_SIZE ; 
 int GFS2_LOCKNAME_LEN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDF_NOJOURNALID ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int control_mount (struct gfs2_sbd*) ; 
 int dlm_new_lockspace (char const*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gfs2_sbd*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_release_lockspace (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_recover_size (struct lm_lockstruct*) ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,...) ; 
 int /*<<< orphan*/  fs_info (struct gfs2_sbd*,char*) ; 
 int /*<<< orphan*/  gdlm_lockspace_ops ; 
 int /*<<< orphan*/  gfs2_control_func ; 
 int /*<<< orphan*/  memcpy (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int set_recover_size (struct gfs2_sbd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  wake_up_bit (scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gdlm_mount(struct gfs2_sbd *sdp, const char *table)
{
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;
	char cluster[GFS2_LOCKNAME_LEN];
	const char *fsname;
	uint32_t flags;
	int error, ops_result;

	/*
	 * initialize everything
	 */

	INIT_DELAYED_WORK(&sdp->sd_control_work, gfs2_control_func);
	spin_lock_init(&ls->ls_recover_spin);
	ls->ls_recover_flags = 0;
	ls->ls_recover_mount = 0;
	ls->ls_recover_start = 0;
	ls->ls_recover_block = 0;
	ls->ls_recover_size = 0;
	ls->ls_recover_submit = NULL;
	ls->ls_recover_result = NULL;
	ls->ls_lvb_bits = NULL;

	error = set_recover_size(sdp, NULL, 0);
	if (error)
		goto fail;

	/*
	 * prepare dlm_new_lockspace args
	 */

	fsname = strchr(table, ':');
	if (!fsname) {
		fs_info(sdp, "no fsname found\n");
		error = -EINVAL;
		goto fail_free;
	}
	memset(cluster, 0, sizeof(cluster));
	memcpy(cluster, table, strlen(table) - strlen(fsname));
	fsname++;

	flags = DLM_LSFL_FS | DLM_LSFL_NEWEXCL;

	/*
	 * create/join lockspace
	 */

	error = dlm_new_lockspace(fsname, cluster, flags, GDLM_LVB_SIZE,
				  &gdlm_lockspace_ops, sdp, &ops_result,
				  &ls->ls_dlm);
	if (error) {
		fs_err(sdp, "dlm_new_lockspace error %d\n", error);
		goto fail_free;
	}

	if (ops_result < 0) {
		/*
		 * dlm does not support ops callbacks,
		 * old dlm_controld/gfs_controld are used, try without ops.
		 */
		fs_info(sdp, "dlm lockspace ops not used\n");
		free_recover_size(ls);
		set_bit(DFL_NO_DLM_OPS, &ls->ls_recover_flags);
		return 0;
	}

	if (!test_bit(SDF_NOJOURNALID, &sdp->sd_flags)) {
		fs_err(sdp, "dlm lockspace ops disallow jid preset\n");
		error = -EINVAL;
		goto fail_release;
	}

	/*
	 * control_mount() uses control_lock to determine first mounter,
	 * and for later mounts, waits for any recoveries to be cleared.
	 */

	error = control_mount(sdp);
	if (error) {
		fs_err(sdp, "mount control error %d\n", error);
		goto fail_release;
	}

	ls->ls_first = !!test_bit(DFL_FIRST_MOUNT, &ls->ls_recover_flags);
	clear_bit(SDF_NOJOURNALID, &sdp->sd_flags);
	smp_mb__after_atomic();
	wake_up_bit(&sdp->sd_flags, SDF_NOJOURNALID);
	return 0;

fail_release:
	dlm_release_lockspace(ls->ls_dlm, 2);
fail_free:
	free_recover_size(ls);
fail:
	return error;
}