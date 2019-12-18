#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
struct super_block {int /*<<< orphan*/  s_root; void* s_time_max; void* s_time_min; int /*<<< orphan*/ * s_d_op; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_flags; struct hpfs_sb_info* s_fs_info; } ;
struct quad_buffer_head {int dummy; } ;
struct TYPE_7__ {scalar_t__ tv_nsec; void* tv_sec; } ;
struct TYPE_6__ {scalar_t__ tv_nsec; void* tv_sec; } ;
struct TYPE_5__ {scalar_t__ tv_nsec; void* tv_sec; } ;
struct inode {int i_size; int i_blocks; int /*<<< orphan*/  i_ino; TYPE_3__ i_ctime; TYPE_2__ i_mtime; TYPE_1__ i_atime; } ;
struct hpfs_super_block {int funcversion; int /*<<< orphan*/  bitmaps; int /*<<< orphan*/  dir_band_bitmap; int /*<<< orphan*/  n_dir_band; int /*<<< orphan*/  dir_band_start; int /*<<< orphan*/  dir_band_end; int /*<<< orphan*/  n_sectors; int /*<<< orphan*/  root; scalar_t__ version; int /*<<< orphan*/  magic; } ;
struct hpfs_spare_block {int dirty; int /*<<< orphan*/  code_page_dir; int /*<<< orphan*/  n_code_pages; int /*<<< orphan*/  n_dnode_spares_free; int /*<<< orphan*/  n_dnode_spares; scalar_t__ old_wrote; scalar_t__ n_spares_used; int /*<<< orphan*/  magic; } ;
struct hpfs_sb_info {int sb_fs_size; int sb_root; int sb_bitmaps; int sb_dirband_start; int sb_dirband_size; int sb_dmap; int sb_mode; int sb_n_free; int sb_n_free_dnodes; int sb_lowercase; int sb_eas; int sb_chk; int sb_chkdsk; int sb_err; int sb_timeshift; int sb_c_bitmap; int sb_max_fwd_alloc; int /*<<< orphan*/ * sb_cp_table; int /*<<< orphan*/  sb_bmp_dir; scalar_t__ sb_was_error; int /*<<< orphan*/  sb_gid; int /*<<< orphan*/  sb_uid; int /*<<< orphan*/  hpfs_mutex; } ;
struct hpfs_dirent {int /*<<< orphan*/  ea_size; int /*<<< orphan*/  creation_date; int /*<<< orphan*/  write_date; int /*<<< orphan*/  read_date; } ;
struct hpfs_boot_block {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
typedef  scalar_t__ dnode_secno ;
struct TYPE_8__ {int i_ea_size; int /*<<< orphan*/  i_parent_dir; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HPFS_SUPER_MAGIC ; 
 int SB_MAGIC ; 
 int /*<<< orphan*/  SB_NOATIME ; 
 int SP_MAGIC ; 
 int U32_MAX ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  current_gid () ; 
 int /*<<< orphan*/  current_uid () ; 
 int current_umask () ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 int /*<<< orphan*/  free_sbi (struct hpfs_sb_info*) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 scalar_t__ hpfs_chk_sectors (struct super_block*,int,int,char*) ; 
 int /*<<< orphan*/  hpfs_dentry_operations ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,...) ; 
 scalar_t__ hpfs_fnode_dno (struct super_block*,int) ; 
 int /*<<< orphan*/  hpfs_help () ; 
 TYPE_4__* hpfs_i (struct inode*) ; 
 int /*<<< orphan*/  hpfs_init_inode (struct inode*) ; 
 int /*<<< orphan*/  hpfs_load_bitmap_directory (struct super_block*,int) ; 
 int /*<<< orphan*/ * hpfs_load_code_page (struct super_block*,int) ; 
 int /*<<< orphan*/  hpfs_load_hotfix_map (struct super_block*,struct hpfs_spare_block*) ; 
 int /*<<< orphan*/  hpfs_lock (struct super_block*) ; 
 void* hpfs_map_sector (struct super_block*,int,struct buffer_head**,int) ; 
 int /*<<< orphan*/  hpfs_read_inode (struct inode*) ; 
 int /*<<< orphan*/  hpfs_sops ; 
 int /*<<< orphan*/  hpfs_unlock (struct super_block*) ; 
 struct inode* iget_locked (struct super_block*,int) ; 
 struct hpfs_sb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* local_to_gmt (struct super_block*,int) ; 
 struct hpfs_dirent* map_dirent (struct inode*,scalar_t__,char*,int,int /*<<< orphan*/ *,struct quad_buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_dirty (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int parse_opts (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  sb_set_blocksize (struct super_block*,int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static int hpfs_fill_super(struct super_block *s, void *options, int silent)
{
	struct buffer_head *bh0, *bh1, *bh2;
	struct hpfs_boot_block *bootblock;
	struct hpfs_super_block *superblock;
	struct hpfs_spare_block *spareblock;
	struct hpfs_sb_info *sbi;
	struct inode *root;

	kuid_t uid;
	kgid_t gid;
	umode_t umask;
	int lowercase, eas, chk, errs, chkdsk, timeshift;

	dnode_secno root_dno;
	struct hpfs_dirent *de = NULL;
	struct quad_buffer_head qbh;

	int o;

	sbi = kzalloc(sizeof(*sbi), GFP_KERNEL);
	if (!sbi) {
		return -ENOMEM;
	}
	s->s_fs_info = sbi;

	mutex_init(&sbi->hpfs_mutex);
	hpfs_lock(s);

	uid = current_uid();
	gid = current_gid();
	umask = current_umask();
	lowercase = 0;
	eas = 2;
	chk = 1;
	errs = 1;
	chkdsk = 1;
	timeshift = 0;

	if (!(o = parse_opts(options, &uid, &gid, &umask, &lowercase,
	    &eas, &chk, &errs, &chkdsk, &timeshift))) {
		pr_err("bad mount options.\n");
		goto bail0;
	}
	if (o==2) {
		hpfs_help();
		goto bail0;
	}

	/*sbi->sb_mounting = 1;*/
	sb_set_blocksize(s, 512);
	sbi->sb_fs_size = -1;
	if (!(bootblock = hpfs_map_sector(s, 0, &bh0, 0))) goto bail1;
	if (!(superblock = hpfs_map_sector(s, 16, &bh1, 1))) goto bail2;
	if (!(spareblock = hpfs_map_sector(s, 17, &bh2, 0))) goto bail3;

	/* Check magics */
	if (/*le16_to_cpu(bootblock->magic) != BB_MAGIC
	    ||*/ le32_to_cpu(superblock->magic) != SB_MAGIC
	    || le32_to_cpu(spareblock->magic) != SP_MAGIC) {
		if (!silent)
			pr_err("Bad magic ... probably not HPFS\n");
		goto bail4;
	}

	/* Check version */
	if (!sb_rdonly(s) && superblock->funcversion != 2 && superblock->funcversion != 3) {
		pr_err("Bad version %d,%d. Mount readonly to go around\n",
			(int)superblock->version, (int)superblock->funcversion);
		pr_err("please try recent version of HPFS driver at http://artax.karlin.mff.cuni.cz/~mikulas/vyplody/hpfs/index-e.cgi and if it still can't understand this format, contact author - mikulas@artax.karlin.mff.cuni.cz\n");
		goto bail4;
	}

	s->s_flags |= SB_NOATIME;

	/* Fill superblock stuff */
	s->s_magic = HPFS_SUPER_MAGIC;
	s->s_op = &hpfs_sops;
	s->s_d_op = &hpfs_dentry_operations;
	s->s_time_min =  local_to_gmt(s, 0);
	s->s_time_max =  local_to_gmt(s, U32_MAX);

	sbi->sb_root = le32_to_cpu(superblock->root);
	sbi->sb_fs_size = le32_to_cpu(superblock->n_sectors);
	sbi->sb_bitmaps = le32_to_cpu(superblock->bitmaps);
	sbi->sb_dirband_start = le32_to_cpu(superblock->dir_band_start);
	sbi->sb_dirband_size = le32_to_cpu(superblock->n_dir_band);
	sbi->sb_dmap = le32_to_cpu(superblock->dir_band_bitmap);
	sbi->sb_uid = uid;
	sbi->sb_gid = gid;
	sbi->sb_mode = 0777 & ~umask;
	sbi->sb_n_free = -1;
	sbi->sb_n_free_dnodes = -1;
	sbi->sb_lowercase = lowercase;
	sbi->sb_eas = eas;
	sbi->sb_chk = chk;
	sbi->sb_chkdsk = chkdsk;
	sbi->sb_err = errs;
	sbi->sb_timeshift = timeshift;
	sbi->sb_was_error = 0;
	sbi->sb_cp_table = NULL;
	sbi->sb_c_bitmap = -1;
	sbi->sb_max_fwd_alloc = 0xffffff;

	if (sbi->sb_fs_size >= 0x80000000) {
		hpfs_error(s, "invalid size in superblock: %08x",
			(unsigned)sbi->sb_fs_size);
		goto bail4;
	}

	if (spareblock->n_spares_used)
		hpfs_load_hotfix_map(s, spareblock);

	/* Load bitmap directory */
	if (!(sbi->sb_bmp_dir = hpfs_load_bitmap_directory(s, le32_to_cpu(superblock->bitmaps))))
		goto bail4;
	
	/* Check for general fs errors*/
	if (spareblock->dirty && !spareblock->old_wrote) {
		if (errs == 2) {
			pr_err("Improperly stopped, not mounted\n");
			goto bail4;
		}
		hpfs_error(s, "improperly stopped");
	}

	if (!sb_rdonly(s)) {
		spareblock->dirty = 1;
		spareblock->old_wrote = 0;
		mark_buffer_dirty(bh2);
	}

	if (le32_to_cpu(spareblock->n_dnode_spares) != le32_to_cpu(spareblock->n_dnode_spares_free)) {
		if (errs >= 2) {
			pr_err("Spare dnodes used, try chkdsk\n");
			mark_dirty(s, 0);
			goto bail4;
		}
		hpfs_error(s, "warning: spare dnodes used, try chkdsk");
		if (errs == 0)
			pr_err("Proceeding, but your filesystem could be corrupted if you delete files or directories\n");
	}
	if (chk) {
		unsigned a;
		if (le32_to_cpu(superblock->dir_band_end) - le32_to_cpu(superblock->dir_band_start) + 1 != le32_to_cpu(superblock->n_dir_band) ||
		    le32_to_cpu(superblock->dir_band_end) < le32_to_cpu(superblock->dir_band_start) || le32_to_cpu(superblock->n_dir_band) > 0x4000) {
			hpfs_error(s, "dir band size mismatch: dir_band_start==%08x, dir_band_end==%08x, n_dir_band==%08x",
				le32_to_cpu(superblock->dir_band_start), le32_to_cpu(superblock->dir_band_end), le32_to_cpu(superblock->n_dir_band));
			goto bail4;
		}
		a = sbi->sb_dirband_size;
		sbi->sb_dirband_size = 0;
		if (hpfs_chk_sectors(s, le32_to_cpu(superblock->dir_band_start), le32_to_cpu(superblock->n_dir_band), "dir_band") ||
		    hpfs_chk_sectors(s, le32_to_cpu(superblock->dir_band_bitmap), 4, "dir_band_bitmap") ||
		    hpfs_chk_sectors(s, le32_to_cpu(superblock->bitmaps), 4, "bitmaps")) {
			mark_dirty(s, 0);
			goto bail4;
		}
		sbi->sb_dirband_size = a;
	} else
		pr_err("You really don't want any checks? You are crazy...\n");

	/* Load code page table */
	if (le32_to_cpu(spareblock->n_code_pages))
		if (!(sbi->sb_cp_table = hpfs_load_code_page(s, le32_to_cpu(spareblock->code_page_dir))))
			pr_err("code page support is disabled\n");

	brelse(bh2);
	brelse(bh1);
	brelse(bh0);

	root = iget_locked(s, sbi->sb_root);
	if (!root)
		goto bail0;
	hpfs_init_inode(root);
	hpfs_read_inode(root);
	unlock_new_inode(root);
	s->s_root = d_make_root(root);
	if (!s->s_root)
		goto bail0;

	/*
	 * find the root directory's . pointer & finish filling in the inode
	 */

	root_dno = hpfs_fnode_dno(s, sbi->sb_root);
	if (root_dno)
		de = map_dirent(root, root_dno, "\001\001", 2, NULL, &qbh);
	if (!de)
		hpfs_error(s, "unable to find root dir");
	else {
		root->i_atime.tv_sec = local_to_gmt(s, le32_to_cpu(de->read_date));
		root->i_atime.tv_nsec = 0;
		root->i_mtime.tv_sec = local_to_gmt(s, le32_to_cpu(de->write_date));
		root->i_mtime.tv_nsec = 0;
		root->i_ctime.tv_sec = local_to_gmt(s, le32_to_cpu(de->creation_date));
		root->i_ctime.tv_nsec = 0;
		hpfs_i(root)->i_ea_size = le32_to_cpu(de->ea_size);
		hpfs_i(root)->i_parent_dir = root->i_ino;
		if (root->i_size == -1)
			root->i_size = 2048;
		if (root->i_blocks == -1)
			root->i_blocks = 5;
		hpfs_brelse4(&qbh);
	}
	hpfs_unlock(s);
	return 0;

bail4:	brelse(bh2);
bail3:	brelse(bh1);
bail2:	brelse(bh0);
bail1:
bail0:
	hpfs_unlock(s);
	free_sbi(sbi);
	return -EINVAL;
}