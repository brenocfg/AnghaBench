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
struct kstatfs {int /*<<< orphan*/  f_namelen; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_files; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_frsize; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct fuse_kstatfs {int /*<<< orphan*/  namelen; int /*<<< orphan*/  ffree; int /*<<< orphan*/  files; int /*<<< orphan*/  bavail; int /*<<< orphan*/  bfree; int /*<<< orphan*/  blocks; int /*<<< orphan*/  frsize; int /*<<< orphan*/  bsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_SUPER_MAGIC ; 

__attribute__((used)) static void convert_fuse_statfs(struct kstatfs *stbuf, struct fuse_kstatfs *attr)
{
	stbuf->f_type    = FUSE_SUPER_MAGIC;
	stbuf->f_bsize   = attr->bsize;
	stbuf->f_frsize  = attr->frsize;
	stbuf->f_blocks  = attr->blocks;
	stbuf->f_bfree   = attr->bfree;
	stbuf->f_bavail  = attr->bavail;
	stbuf->f_files   = attr->files;
	stbuf->f_ffree   = attr->ffree;
	stbuf->f_namelen = attr->namelen;
	/* fsid is left zero */
}