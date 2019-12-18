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
struct stat64 {int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_blocks; int /*<<< orphan*/  st_blksize; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_ino; } ;
struct TYPE_6__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct hostfs_stat {int /*<<< orphan*/  min; int /*<<< orphan*/  maj; int /*<<< orphan*/  blocks; int /*<<< orphan*/  blksize; TYPE_3__ mtime; TYPE_2__ ctime; TYPE_1__ atime; int /*<<< orphan*/  size; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  nlink; int /*<<< orphan*/  mode; int /*<<< orphan*/  ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_minor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stat64_to_hostfs(const struct stat64 *buf, struct hostfs_stat *p)
{
	p->ino = buf->st_ino;
	p->mode = buf->st_mode;
	p->nlink = buf->st_nlink;
	p->uid = buf->st_uid;
	p->gid = buf->st_gid;
	p->size = buf->st_size;
	p->atime.tv_sec = buf->st_atime;
	p->atime.tv_nsec = 0;
	p->ctime.tv_sec = buf->st_ctime;
	p->ctime.tv_nsec = 0;
	p->mtime.tv_sec = buf->st_mtime;
	p->mtime.tv_nsec = 0;
	p->blksize = buf->st_blksize;
	p->blocks = buf->st_blocks;
	p->maj = os_major(buf->st_rdev);
	p->min = os_minor(buf->st_rdev);
}