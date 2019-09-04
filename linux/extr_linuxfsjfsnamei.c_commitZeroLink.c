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
typedef  int /*<<< orphan*/  tid_t ;
struct tblock {int /*<<< orphan*/  xflag; } ;
struct inode {int i_mode; scalar_t__ i_size; } ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_3__ {int flag; } ;
struct TYPE_4__ {TYPE_1__ acl; TYPE_1__ ea; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_Freewmap ; 
 int /*<<< orphan*/  COMMIT_PMAP ; 
 int DXD_EXTENT ; 
 scalar_t__ IDATASIZE ; 
 TYPE_2__* JFS_IP (struct inode*) ; 
 int S_IFDIR ; 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jfs_info (char*,int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  set_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 struct tblock* tid_to_tblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txEA (int /*<<< orphan*/ ,struct inode*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xtTruncate_pmap (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s64 commitZeroLink(tid_t tid, struct inode *ip)
{
	int filetype;
	struct tblock *tblk;

	jfs_info("commitZeroLink: tid = %d, ip = 0x%p", tid, ip);

	filetype = ip->i_mode & S_IFMT;
	switch (filetype) {
	case S_IFREG:
		break;
	case S_IFLNK:
		/* fast symbolic link */
		if (ip->i_size < IDATASIZE) {
			ip->i_size = 0;
			return 0;
		}
		break;
	default:
		assert(filetype != S_IFDIR);
		return 0;
	}

	set_cflag(COMMIT_Freewmap, ip);

	/* mark transaction of block map update type */
	tblk = tid_to_tblock(tid);
	tblk->xflag |= COMMIT_PMAP;

	/*
	 * free EA
	 */
	if (JFS_IP(ip)->ea.flag & DXD_EXTENT)
		/* acquire maplock on EA to be freed from block map */
		txEA(tid, ip, &JFS_IP(ip)->ea, NULL);

	/*
	 * free ACL
	 */
	if (JFS_IP(ip)->acl.flag & DXD_EXTENT)
		/* acquire maplock on EA to be freed from block map */
		txEA(tid, ip, &JFS_IP(ip)->acl, NULL);

	/*
	 * free xtree/data (truncate to zero length):
	 * free xtree/data pages from cache if COMMIT_PWMAP,
	 * free xtree/data blocks from persistent block map, and
	 * free xtree/data blocks from working block map if COMMIT_PWMAP;
	 */
	if (ip->i_size)
		return xtTruncate_pmap(tid, ip, 0);

	return 0;
}