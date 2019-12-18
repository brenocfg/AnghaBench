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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {scalar_t__ st_uid; scalar_t__ st_gid; int st_mode; int st_ino; int st_size; int st_atime; int st_mtime; int st_ctime; int st_dev; int st_nlink; int st_rdev; int st_blksize; int st_blocks; } ;
typedef  TYPE_1__ zend_stat_t ;
typedef  int /*<<< orphan*/  zend_long ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTICE ; 
 int /*<<< orphan*/  E_WARNING ; 
#define  FS_ATIME 147 
#define  FS_CTIME 146 
#define  FS_EXISTS 145 
#define  FS_GROUP 144 
#define  FS_INODE 143 
#define  FS_IS_DIR 142 
#define  FS_IS_FILE 141 
#define  FS_IS_LINK 140 
#define  FS_IS_R 139 
#define  FS_IS_W 138 
#define  FS_IS_X 137 
#define  FS_LSTAT 136 
#define  FS_MTIME 135 
#define  FS_OWNER 134 
#define  FS_PERMS 133 
#define  FS_SIZE 132 
#define  FS_STAT 131 
#define  FS_TYPE 130 
 int /*<<< orphan*/  RETURN_BOOL (int) ; 
 int /*<<< orphan*/  RETURN_FALSE ; 
 int /*<<< orphan*/  RETURN_LONG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_STRING (char*) ; 
 int /*<<< orphan*/  RETURN_TRUE ; 
#define  S_IFDIR 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_ISDIR (int) ; 
 int S_ISLNK (int) ; 
 int S_ISREG (int) ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (scalar_t__*) ; 
 scalar_t__ getgid () ; 
 int getgroups (int,scalar_t__*) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ safe_emalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  zend_hash_next_index_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_str_update (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void phar_fancy_stat(zend_stat_t *stat_sb, int type, zval *return_value)
{
	zval stat_dev, stat_ino, stat_mode, stat_nlink, stat_uid, stat_gid, stat_rdev,
		 stat_size, stat_atime, stat_mtime, stat_ctime, stat_blksize, stat_blocks;
	int rmask=S_IROTH, wmask=S_IWOTH, xmask=S_IXOTH; /* access rights defaults to other */
	char *stat_sb_names[13] = {
		"dev", "ino", "mode", "nlink", "uid", "gid", "rdev",
		"size", "atime", "mtime", "ctime", "blksize", "blocks"
	};

	if (type >= FS_IS_W && type <= FS_IS_X) {
		if(stat_sb->st_uid==getuid()) {
			rmask=S_IRUSR;
			wmask=S_IWUSR;
			xmask=S_IXUSR;
		} else if(stat_sb->st_gid==getgid()) {
			rmask=S_IRGRP;
			wmask=S_IWGRP;
			xmask=S_IXGRP;
		} else {
			int   groups, n, i;
			gid_t *gids;

			groups = getgroups(0, NULL);
			if(groups > 0) {
				gids=(gid_t *)safe_emalloc(groups, sizeof(gid_t), 0);
				n=getgroups(groups, gids);
				for(i=0;i<n;++i){
					if(stat_sb->st_gid==gids[i]) {
						rmask=S_IRGRP;
						wmask=S_IWGRP;
						xmask=S_IXGRP;
						break;
					}
				}
				efree(gids);
			}
		}
	}

	switch (type) {
	case FS_PERMS:
		RETURN_LONG((zend_long)stat_sb->st_mode);
	case FS_INODE:
		RETURN_LONG((zend_long)stat_sb->st_ino);
	case FS_SIZE:
		RETURN_LONG((zend_long)stat_sb->st_size);
	case FS_OWNER:
		RETURN_LONG((zend_long)stat_sb->st_uid);
	case FS_GROUP:
		RETURN_LONG((zend_long)stat_sb->st_gid);
	case FS_ATIME:
		RETURN_LONG((zend_long)stat_sb->st_atime);
	case FS_MTIME:
		RETURN_LONG((zend_long)stat_sb->st_mtime);
	case FS_CTIME:
		RETURN_LONG((zend_long)stat_sb->st_ctime);
	case FS_TYPE:
		if (S_ISLNK(stat_sb->st_mode)) {
			RETURN_STRING("link");
		}
		switch(stat_sb->st_mode & S_IFMT) {
		case S_IFDIR: RETURN_STRING("dir");
		case S_IFREG: RETURN_STRING("file");
		}
		php_error_docref(NULL, E_NOTICE, "Unknown file type (%u)", stat_sb->st_mode & S_IFMT);
		RETURN_STRING("unknown");
	case FS_IS_W:
		RETURN_BOOL((stat_sb->st_mode & wmask) != 0);
	case FS_IS_R:
		RETURN_BOOL((stat_sb->st_mode&rmask)!=0);
	case FS_IS_X:
		RETURN_BOOL((stat_sb->st_mode&xmask)!=0 && !S_ISDIR(stat_sb->st_mode));
	case FS_IS_FILE:
		RETURN_BOOL(S_ISREG(stat_sb->st_mode));
	case FS_IS_DIR:
		RETURN_BOOL(S_ISDIR(stat_sb->st_mode));
	case FS_IS_LINK:
		RETURN_BOOL(S_ISLNK(stat_sb->st_mode));
	case FS_EXISTS:
		RETURN_TRUE; /* the false case was done earlier */
	case FS_LSTAT:
		/* FALLTHROUGH */
	case FS_STAT:
		array_init(return_value);

		ZVAL_LONG(&stat_dev, stat_sb->st_dev);
		ZVAL_LONG(&stat_ino, stat_sb->st_ino);
		ZVAL_LONG(&stat_mode, stat_sb->st_mode);
		ZVAL_LONG(&stat_nlink, stat_sb->st_nlink);
		ZVAL_LONG(&stat_uid, stat_sb->st_uid);
		ZVAL_LONG(&stat_gid, stat_sb->st_gid);
#ifdef HAVE_STRUCT_STAT_ST_RDEV
		ZVAL_LONG(&stat_rdev, stat_sb->st_rdev);
#else
		ZVAL_LONG(&stat_rdev, -1);
#endif
		ZVAL_LONG(&stat_size, stat_sb->st_size);
		ZVAL_LONG(&stat_atime, stat_sb->st_atime);
		ZVAL_LONG(&stat_mtime, stat_sb->st_mtime);
		ZVAL_LONG(&stat_ctime, stat_sb->st_ctime);
#ifdef HAVE_STRUCT_STAT_ST_BLKSIZE
		ZVAL_LONG(&stat_blksize, stat_sb->st_blksize);
#else
		ZVAL_LONG(&stat_blksize,-1);
#endif
#ifdef HAVE_STRUCT_STAT_ST_BLOCKS
		ZVAL_LONG(&stat_blocks, stat_sb->st_blocks);
#else
		ZVAL_LONG(&stat_blocks,-1);
#endif
		/* Store numeric indexes in proper order */
		zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &stat_dev);
		zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &stat_ino);
		zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &stat_mode);
		zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &stat_nlink);
		zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &stat_uid);
		zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &stat_gid);

		zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &stat_rdev);
		zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &stat_size);
		zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &stat_atime);
		zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &stat_mtime);
		zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &stat_ctime);
		zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &stat_blksize);
		zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &stat_blocks);

		/* Store string indexes referencing the same zval*/
		zend_hash_str_update(Z_ARRVAL_P(return_value), stat_sb_names[0], strlen(stat_sb_names[0]), &stat_dev);
		zend_hash_str_update(Z_ARRVAL_P(return_value), stat_sb_names[1], strlen(stat_sb_names[1]), &stat_ino);
		zend_hash_str_update(Z_ARRVAL_P(return_value), stat_sb_names[2], strlen(stat_sb_names[2]), &stat_mode);
		zend_hash_str_update(Z_ARRVAL_P(return_value), stat_sb_names[3], strlen(stat_sb_names[3]), &stat_nlink);
		zend_hash_str_update(Z_ARRVAL_P(return_value), stat_sb_names[4], strlen(stat_sb_names[4]), &stat_uid);
		zend_hash_str_update(Z_ARRVAL_P(return_value), stat_sb_names[5], strlen(stat_sb_names[5]), &stat_gid);
		zend_hash_str_update(Z_ARRVAL_P(return_value), stat_sb_names[6], strlen(stat_sb_names[6]), &stat_rdev);
		zend_hash_str_update(Z_ARRVAL_P(return_value), stat_sb_names[7], strlen(stat_sb_names[7]), &stat_size);
		zend_hash_str_update(Z_ARRVAL_P(return_value), stat_sb_names[8], strlen(stat_sb_names[8]), &stat_atime);
		zend_hash_str_update(Z_ARRVAL_P(return_value), stat_sb_names[9], strlen(stat_sb_names[9]), &stat_mtime);
		zend_hash_str_update(Z_ARRVAL_P(return_value), stat_sb_names[10], strlen(stat_sb_names[10]), &stat_ctime);
		zend_hash_str_update(Z_ARRVAL_P(return_value), stat_sb_names[11], strlen(stat_sb_names[11]), &stat_blksize);
		zend_hash_str_update(Z_ARRVAL_P(return_value), stat_sb_names[12], strlen(stat_sb_names[12]), &stat_blocks);

		return;
	}
	php_error_docref(NULL, E_WARNING, "Didn't understand stat call");
	RETURN_FALSE;
}