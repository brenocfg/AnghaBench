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
struct smb_vol {int /*<<< orphan*/  prepath; } ;
struct cifs_tcon {int /*<<< orphan*/  treeName; } ;
struct cifs_sb_info {int dummy; } ;

/* Variables and functions */
 char CIFS_DIR_SEP (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAX_TREE_SIZE ; 
 int /*<<< orphan*/  convert_delimiter (char*,char) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int strnlen (int /*<<< orphan*/ ,scalar_t__) ; 

char *
cifs_build_path_to_root(struct smb_vol *vol, struct cifs_sb_info *cifs_sb,
			struct cifs_tcon *tcon, int add_treename)
{
	int pplen = vol->prepath ? strlen(vol->prepath) + 1 : 0;
	int dfsplen;
	char *full_path = NULL;

	/* if no prefix path, simply set path to the root of share to "" */
	if (pplen == 0) {
		full_path = kzalloc(1, GFP_KERNEL);
		return full_path;
	}

	if (add_treename)
		dfsplen = strnlen(tcon->treeName, MAX_TREE_SIZE + 1);
	else
		dfsplen = 0;

	full_path = kmalloc(dfsplen + pplen + 1, GFP_KERNEL);
	if (full_path == NULL)
		return full_path;

	if (dfsplen)
		memcpy(full_path, tcon->treeName, dfsplen);
	full_path[dfsplen] = CIFS_DIR_SEP(cifs_sb);
	memcpy(full_path + dfsplen + 1, vol->prepath, pplen);
	convert_delimiter(full_path, CIFS_DIR_SEP(cifs_sb));
	return full_path;
}