#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pxd_lock {int /*<<< orphan*/  pxd; void* flag; } ;
struct maplock {int index; } ;
struct inode {int i_mode; scalar_t__ i_size; } ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_5__ {int flag; } ;
struct TYPE_6__ {TYPE_1__ acl; TYPE_1__ ea; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_WMAP ; 
 int DXD_EXTENT ; 
 scalar_t__ IDATASIZE ; 
 TYPE_4__* JFS_IP (struct inode*) ; 
 int /*<<< orphan*/  PXDaddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PXDlength (int /*<<< orphan*/ *,int) ; 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  addressDXD (TYPE_1__*) ; 
 int /*<<< orphan*/  invalidate_dxd_metapages (struct inode*,TYPE_1__) ; 
 int /*<<< orphan*/  jfs_info (char*,struct inode*) ; 
 int lengthDXD (TYPE_1__*) ; 
 void* mlckFREEPXD ; 
 int /*<<< orphan*/  txFreeMap (struct inode*,struct pxd_lock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtTruncate (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void jfs_free_zero_link(struct inode *ip)
{
	int type;

	jfs_info("jfs_free_zero_link: ip = 0x%p", ip);

	/* return if not reg or symbolic link or if size is
	 * already ok.
	 */
	type = ip->i_mode & S_IFMT;

	switch (type) {
	case S_IFREG:
		break;
	case S_IFLNK:
		/* if its contained in inode nothing to do */
		if (ip->i_size < IDATASIZE)
			return;
		break;
	default:
		return;
	}

	/*
	 * free EA
	 */
	if (JFS_IP(ip)->ea.flag & DXD_EXTENT) {
		s64 xaddr = addressDXD(&JFS_IP(ip)->ea);
		int xlen = lengthDXD(&JFS_IP(ip)->ea);
		struct maplock maplock;	/* maplock for COMMIT_WMAP */
		struct pxd_lock *pxdlock;	/* maplock for COMMIT_WMAP */

		/* free EA pages from cache */
		invalidate_dxd_metapages(ip, JFS_IP(ip)->ea);

		/* free EA extent from working block map */
		maplock.index = 1;
		pxdlock = (struct pxd_lock *) & maplock;
		pxdlock->flag = mlckFREEPXD;
		PXDaddress(&pxdlock->pxd, xaddr);
		PXDlength(&pxdlock->pxd, xlen);
		txFreeMap(ip, pxdlock, NULL, COMMIT_WMAP);
	}

	/*
	 * free ACL
	 */
	if (JFS_IP(ip)->acl.flag & DXD_EXTENT) {
		s64 xaddr = addressDXD(&JFS_IP(ip)->acl);
		int xlen = lengthDXD(&JFS_IP(ip)->acl);
		struct maplock maplock;	/* maplock for COMMIT_WMAP */
		struct pxd_lock *pxdlock;	/* maplock for COMMIT_WMAP */

		invalidate_dxd_metapages(ip, JFS_IP(ip)->acl);

		/* free ACL extent from working block map */
		maplock.index = 1;
		pxdlock = (struct pxd_lock *) & maplock;
		pxdlock->flag = mlckFREEPXD;
		PXDaddress(&pxdlock->pxd, xaddr);
		PXDlength(&pxdlock->pxd, xlen);
		txFreeMap(ip, pxdlock, NULL, COMMIT_WMAP);
	}

	/*
	 * free xtree/data (truncate to zero length):
	 * free xtree/data pages from cache, and
	 * free xtree/data blocks from working block map;
	 */
	if (ip->i_size)
		xtTruncate(0, ip, 0, COMMIT_WMAP);
}