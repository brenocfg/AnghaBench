#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cifs_tcon {int /*<<< orphan*/  fscache; } ;
struct cifs_fscache_inode_auxdata {int /*<<< orphan*/  last_change_time_nsec; int /*<<< orphan*/  last_write_time_nsec; int /*<<< orphan*/  last_change_time_sec; int /*<<< orphan*/  last_write_time_sec; int /*<<< orphan*/  eof; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_size; TYPE_2__ i_ctime; TYPE_1__ i_mtime; } ;
struct cifsInodeInfo {TYPE_3__ vfs_inode; int /*<<< orphan*/  uniqueid; int /*<<< orphan*/  fscache; int /*<<< orphan*/  server_eof; } ;
typedef  int /*<<< orphan*/  auxdata ;

/* Variables and functions */
 int /*<<< orphan*/  cifs_fscache_inode_object_def ; 
 int /*<<< orphan*/  fscache_acquire_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct cifs_fscache_inode_auxdata*,int,struct cifsInodeInfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct cifs_fscache_inode_auxdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cifs_fscache_acquire_inode_cookie(struct cifsInodeInfo *cifsi,
					      struct cifs_tcon *tcon)
{
	struct cifs_fscache_inode_auxdata auxdata;

	memset(&auxdata, 0, sizeof(auxdata));
	auxdata.eof = cifsi->server_eof;
	auxdata.last_write_time_sec = cifsi->vfs_inode.i_mtime.tv_sec;
	auxdata.last_change_time_sec = cifsi->vfs_inode.i_ctime.tv_sec;
	auxdata.last_write_time_nsec = cifsi->vfs_inode.i_mtime.tv_nsec;
	auxdata.last_change_time_nsec = cifsi->vfs_inode.i_ctime.tv_nsec;

	cifsi->fscache =
		fscache_acquire_cookie(tcon->fscache,
				       &cifs_fscache_inode_object_def,
				       &cifsi->uniqueid, sizeof(cifsi->uniqueid),
				       &auxdata, sizeof(auxdata),
				       cifsi, cifsi->vfs_inode.i_size, true);
}