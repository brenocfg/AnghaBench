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
typedef  int umode_t ;
struct path {struct dentry* dentry; int /*<<< orphan*/  mnt; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IALLUGO ; 
#define  S_IFBLK 131 
#define  S_IFCHR 130 
#define  S_IFIFO 129 
 int S_IFMT ; 
#define  S_IFSOCK 128 
 int TOMOYO_TYPE_CREATE ; 
 int TOMOYO_TYPE_MKBLOCK ; 
 int TOMOYO_TYPE_MKCHAR ; 
 int TOMOYO_TYPE_MKFIFO ; 
 int TOMOYO_TYPE_MKSOCK ; 
 int tomoyo_mkdev_perm (int,struct path*,unsigned int const,unsigned int) ; 
 int tomoyo_path_number_perm (int,struct path*,unsigned int const) ; 

__attribute__((used)) static int tomoyo_path_mknod(const struct path *parent, struct dentry *dentry,
			     umode_t mode, unsigned int dev)
{
	struct path path = { .mnt = parent->mnt, .dentry = dentry };
	int type = TOMOYO_TYPE_CREATE;
	const unsigned int perm = mode & S_IALLUGO;

	switch (mode & S_IFMT) {
	case S_IFCHR:
		type = TOMOYO_TYPE_MKCHAR;
		break;
	case S_IFBLK:
		type = TOMOYO_TYPE_MKBLOCK;
		break;
	default:
		goto no_dev;
	}
	return tomoyo_mkdev_perm(type, &path, perm, dev);
 no_dev:
	switch (mode & S_IFMT) {
	case S_IFIFO:
		type = TOMOYO_TYPE_MKFIFO;
		break;
	case S_IFSOCK:
		type = TOMOYO_TYPE_MKSOCK;
		break;
	}
	return tomoyo_path_number_perm(type, &path, perm);
}