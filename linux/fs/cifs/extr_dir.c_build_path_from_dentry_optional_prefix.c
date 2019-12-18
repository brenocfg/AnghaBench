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
struct TYPE_2__ {int len; int /*<<< orphan*/  name; } ;
struct dentry {struct dentry* d_parent; int /*<<< orphan*/  d_lock; TYPE_1__ d_name; int /*<<< orphan*/  d_sb; } ;
struct cifs_tcon {int /*<<< orphan*/  treeName; } ;
struct cifs_sb_info {int mnt_cifs_flags; char* prepath; } ;

/* Variables and functions */
 char CIFS_DIR_SEP (struct cifs_sb_info*) ; 
 int CIFS_MOUNT_POSIX_PATHS ; 
 int CIFS_MOUNT_USE_PREFIX_PATH ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 scalar_t__ MAX_TREE_SIZE ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 struct cifs_tcon* cifs_sb_master_tcon (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  rename_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 int strnlen (int /*<<< orphan*/ ,scalar_t__) ; 

char *
build_path_from_dentry_optional_prefix(struct dentry *direntry, bool prefix)
{
	struct dentry *temp;
	int namelen;
	int dfsplen;
	int pplen = 0;
	char *full_path;
	char dirsep;
	struct cifs_sb_info *cifs_sb = CIFS_SB(direntry->d_sb);
	struct cifs_tcon *tcon = cifs_sb_master_tcon(cifs_sb);
	unsigned seq;

	dirsep = CIFS_DIR_SEP(cifs_sb);
	if (prefix)
		dfsplen = strnlen(tcon->treeName, MAX_TREE_SIZE + 1);
	else
		dfsplen = 0;

	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_USE_PREFIX_PATH)
		pplen = cifs_sb->prepath ? strlen(cifs_sb->prepath) + 1 : 0;

cifs_bp_rename_retry:
	namelen = dfsplen + pplen;
	seq = read_seqbegin(&rename_lock);
	rcu_read_lock();
	for (temp = direntry; !IS_ROOT(temp);) {
		namelen += (1 + temp->d_name.len);
		temp = temp->d_parent;
		if (temp == NULL) {
			cifs_dbg(VFS, "corrupt dentry\n");
			rcu_read_unlock();
			return NULL;
		}
	}
	rcu_read_unlock();

	full_path = kmalloc(namelen+1, GFP_ATOMIC);
	if (full_path == NULL)
		return full_path;
	full_path[namelen] = 0;	/* trailing null */
	rcu_read_lock();
	for (temp = direntry; !IS_ROOT(temp);) {
		spin_lock(&temp->d_lock);
		namelen -= 1 + temp->d_name.len;
		if (namelen < 0) {
			spin_unlock(&temp->d_lock);
			break;
		} else {
			full_path[namelen] = dirsep;
			strncpy(full_path + namelen + 1, temp->d_name.name,
				temp->d_name.len);
			cifs_dbg(FYI, "name: %s\n", full_path + namelen);
		}
		spin_unlock(&temp->d_lock);
		temp = temp->d_parent;
		if (temp == NULL) {
			cifs_dbg(VFS, "corrupt dentry\n");
			rcu_read_unlock();
			kfree(full_path);
			return NULL;
		}
	}
	rcu_read_unlock();
	if (namelen != dfsplen + pplen || read_seqretry(&rename_lock, seq)) {
		cifs_dbg(FYI, "did not end path lookup where expected. namelen=%ddfsplen=%d\n",
			 namelen, dfsplen);
		/* presumably this is only possible if racing with a rename
		of one of the parent directories  (we can not lock the dentries
		above us to prevent this, but retrying should be harmless) */
		kfree(full_path);
		goto cifs_bp_rename_retry;
	}
	/* DIR_SEP already set for byte  0 / vs \ but not for
	   subsequent slashes in prepath which currently must
	   be entered the right way - not sure if there is an alternative
	   since the '\' is a valid posix character so we can not switch
	   those safely to '/' if any are found in the middle of the prepath */
	/* BB test paths to Windows with '/' in the midst of prepath */

	if (pplen) {
		int i;

		cifs_dbg(FYI, "using cifs_sb prepath <%s>\n", cifs_sb->prepath);
		memcpy(full_path+dfsplen+1, cifs_sb->prepath, pplen-1);
		full_path[dfsplen] = dirsep;
		for (i = 0; i < pplen-1; i++)
			if (full_path[dfsplen+1+i] == '/')
				full_path[dfsplen+1+i] = CIFS_DIR_SEP(cifs_sb);
	}

	if (dfsplen) {
		strncpy(full_path, tcon->treeName, dfsplen);
		if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_POSIX_PATHS) {
			int i;
			for (i = 0; i < dfsplen; i++) {
				if (full_path[i] == '\\')
					full_path[i] = '/';
			}
		}
	}
	return full_path;
}