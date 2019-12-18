#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pinned_obj_table {int /*<<< orphan*/  table; } ;
struct pinned_obj {int /*<<< orphan*/  id; int /*<<< orphan*/  hash; int /*<<< orphan*/  path; } ;
struct mntent {char* mnt_dir; int /*<<< orphan*/  mnt_type; } ;
struct bpf_prog_info {int /*<<< orphan*/  id; int /*<<< orphan*/  hash; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  pinned_info ;
typedef  enum bpf_obj_type { ____Placeholder_bpf_obj_type } bpf_obj_type ;
typedef  int __u32 ;
struct TYPE_3__ {int fts_info; int /*<<< orphan*/  fts_path; } ;
typedef  TYPE_1__ FTSENT ;
typedef  int /*<<< orphan*/  FTS ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FTS_F ; 
 int bpf_obj_get_info_by_fd (int,struct pinned_obj*,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts_open (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* fts_read (int /*<<< orphan*/ *) ; 
 int get_fd_type (int) ; 
 struct mntent* getmntent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pinned_obj* malloc (int) ; 
 int /*<<< orphan*/  memset (struct pinned_obj*,int /*<<< orphan*/ ,int) ; 
 int open_obj_pinned (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * setmntent (char*,char*) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

int build_pinned_obj_table(struct pinned_obj_table *tab,
			   enum bpf_obj_type type)
{
	struct bpf_prog_info pinned_info = {};
	struct pinned_obj *obj_node = NULL;
	__u32 len = sizeof(pinned_info);
	struct mntent *mntent = NULL;
	enum bpf_obj_type objtype;
	FILE *mntfile = NULL;
	FTSENT *ftse = NULL;
	FTS *fts = NULL;
	int fd, err;

	mntfile = setmntent("/proc/mounts", "r");
	if (!mntfile)
		return -1;

	while ((mntent = getmntent(mntfile))) {
		char *path[] = { mntent->mnt_dir, NULL };

		if (strncmp(mntent->mnt_type, "bpf", 3) != 0)
			continue;

		fts = fts_open(path, 0, NULL);
		if (!fts)
			continue;

		while ((ftse = fts_read(fts))) {
			if (!(ftse->fts_info & FTS_F))
				continue;
			fd = open_obj_pinned(ftse->fts_path, true);
			if (fd < 0)
				continue;

			objtype = get_fd_type(fd);
			if (objtype != type) {
				close(fd);
				continue;
			}
			memset(&pinned_info, 0, sizeof(pinned_info));
			err = bpf_obj_get_info_by_fd(fd, &pinned_info, &len);
			if (err) {
				close(fd);
				continue;
			}

			obj_node = malloc(sizeof(*obj_node));
			if (!obj_node) {
				close(fd);
				fts_close(fts);
				fclose(mntfile);
				return -1;
			}

			memset(obj_node, 0, sizeof(*obj_node));
			obj_node->id = pinned_info.id;
			obj_node->path = strdup(ftse->fts_path);
			hash_add(tab->table, &obj_node->hash, obj_node->id);

			close(fd);
		}
		fts_close(fts);
	}
	fclose(mntfile);
	return 0;
}